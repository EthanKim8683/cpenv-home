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

const int INF = 1e18;

template <class S, auto op, auto e>
struct segtree {
  int n;
  vc<S> s;
  segtree(const vc<S> &v) : n(sz(v)), s(2 * n) {
    rep(i, 0, n) s[n + i] = v[i];
    for (int i = n - 1; i > 0; i--) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  segtree(int m) : segtree(vc(m, e())) {}
  S get(int i) { return s[n + i]; }
  void set(int i, S t) {
    for (s[i += n] = t; i >>= 1;) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  S prod(int l, int r) {
    S lv = e(), rv = e();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, s[l++]);
      if (r & 1) rv = op(s[--r], rv);
    }
    return op(lv, rv);
  }
  S all_prod() { return s[1]; }
};

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

    vi A(N);
    for (auto &e : A) cin >> e;

    int logn = __lg(2 * N - 1), pown = 1ll << logn;
    struct S {
      int l, r, n, k;
    };
    auto op = [&](S a, S b) -> S {
      return {min(a.l, b.l), max(a.r, b.r), a.n + b.n,
              a.r > b.l ? a.n : max(a.k, b.k)};
    };
    auto e = [&]() -> S { return {INF, -INF, 0, 0}; };
    segtree<S, op, e> st(pown);
    auto f = [&](int x) -> S { return {x, x, 1, 0}; };
    rep(i, 0, N) { st.set(i, f(A[i])); }
    rep(i, N, pown) { st.set(i, f(INF)); }

    cout << st.all_prod().k << '\n';

    while (Q--) {
      int i, x;
      cin >> i >> x;

      st.set(i, f(x));
      cout << st.all_prod().k << '\n';
    }
  }
}
