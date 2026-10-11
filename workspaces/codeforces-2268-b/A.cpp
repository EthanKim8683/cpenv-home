#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

// #define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi combos;
  rep(i, 0, 1 << 5) {
    int sum = 0;
    rep(j, 0, 5) {
      if (~i >> j & 1) continue;
      sum ^= 3 * (j + 1);
    }
    combos.pb(sum);
  }
  sort(all(combos));
  combos.erase(unique(all(combos)), combos.end());
  // cerr << sz(combos) << '\n';
  // for (auto e : combos) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';

  // rep(i, 0, 16) {
  //   bool found = false;
  //   for (auto e : combos) {
  //     found = found or (i ^ e) % 3 == 0;
  //   }
  //   cerr << found << ' ';
  // }
  // cerr << '\n';

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    using S = array<array<int, 8>, 8>;
    auto op = [&](S a, S b) -> S {
      S rv{};
      rep(i, 0, 8) {
        rep(j, 0, 8) {
          rep(k, 0, 8) { chmax(rv[i][j], a[i][k] + b[k][j]); }
        }
      }
      return rv;
    };
    auto e = [&]() -> S { return S{}; };
    auto f = [&](int x) -> S {
      S rv{};
      rep(i, 0, 8) {
        rep(j, 0, 8) {
          rv[i][j] = (x ^ combos[i] ^ combos[j]) % 3 == 0 ? 1 : 0;
        }
      }
      return rv;
    };
    vc<S> st(2 * N);
    rep(i, 0, N) { st[N + i] = f(A[i]); }
    for (int i = N - 1; i >= 1; i--) {
      st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
    auto set = [&](int i, S x) -> void {
      for (st[i += N] = x; i >>= 1;) {
        st[i] = op(st[i << 1], st[i << 1 | 1]);
      }
    };
    auto prod = [&](int l, int r) -> S {
      S lrv = e(), rrv = e();
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) lrv = op(lrv, st[l++]);
        if (r & 1) rrv = op(st[--r], rrv);
      }
      return op(lrv, rrv);
    };
    auto g = [&](S x) -> int { return x[0][0]; };
    cout << g(prod(0, N)) << ' ';
    while (Q--) {
      int p, x;
      cin >> p >> x;
      p--;
      set(p, f(x));
      cout << g(prod(0, N)) << ' ';
    }
    cout << '\n';
  }
}
