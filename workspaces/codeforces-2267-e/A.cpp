#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
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

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    string S;
    cin >> S;

    using T = struct {
      int contrib_sum, weight_sum;
      array<int, 2> counts;
      int sum;
    };
    auto op = [&](T a, T b) -> T {
      int contrib_sum = a.contrib_sum + b.contrib_sum + a.sum * b.weight_sum;
      int weight_sum = a.weight_sum + b.weight_sum;
      array<int, 2> counts = {0, 0};
      rep(i, 0, 2) {
        counts[i] += a.counts[i];
        counts[i ^ a.sum & 1] += b.counts[i];
      }
      int sum = a.sum + b.sum;
      return {contrib_sum, weight_sum, counts, sum};
    };
    auto e = [&]() -> T { return {0, 0, {0, 0}, 0}; };
    vc<T> st(2 * N, e());
    auto f = [&](int i, int x) -> T { return {0, i - (N - 1 - i), {1, 0}, x}; };
    rep(i, 0, N - 1) { st[N + i] = f(i, S[i] ^ S[i + 1]); }
    st[N + N - 1] = f(N - 1, 0);
    for (int i = N - 1; i >= 1; i--) {
      st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
    auto set = [&](int i, T x) -> void {
      for (st[i += N] = x; i >>= 1;) {
        st[i] = op(st[i << 1], st[i << 1 | 1]);
      }
    };
    auto prod = [&](int l, int r) -> T {
      T lrv = e(), rrv = e();
      for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
        if (l & 1) lrv = op(lrv, st[l++]);
        if (r & 1) rrv = op(st[--r], rrv);
      }
      return op(lrv, rrv);
    };
    auto g = [&](T x) -> int {
      return (x.contrib_sum + x.counts[0] * x.counts[1]) / 2;
    };
    cout << g(prod(0, N)) << ' ';
    while (Q--) {
      int i;
      cin >> i;
      i--;
      S[i] ^= 1;
      if (i - 1 >= 0) {
        set(i - 1, f(i - 1, S[i - 1] ^ S[i]));
      }
      if (i < N - 1) {
        set(i, f(i, S[i] ^ S[i + 1]));
      }
      cout << g(prod(0, N)) << ' ';
    }
    cout << '\n';
  }
}
