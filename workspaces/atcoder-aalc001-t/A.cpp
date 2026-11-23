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

template <class S, auto op, auto e, class F, auto mp, auto cp, auto id>
struct lazy_segtree {
  int lgn, n;
  vc<S> s;
  vc<F> f;
  lazy_segtree(const vc<S> &v)
      : lgn(__lg(2 * sz(v) - 1)), n(1 << lgn), s(2 * n), f(2 * n, id()) {
    rep(i, 0, sz(v)) s[n + i] = v[i];
    for (int i = n - 1; i > 0; i--) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  lazy_segtree(int m) : lazy_segtree(vc(m, e())) {}
  void ch(int i, F g) {
    s[i] = mp(g, s[i]);
    if (i < n) f[i] = cp(f[i], g);
  }
  void push(int i) {
    for (int j = lgn; j > 0; j--) {
      int k = (i + n) >> j;
      ch(k << 1, f[k]);
      ch(k << 1 | 1, f[k]);
      f[k] = id();
    }
  }
  void pull(int i) {
    for (i += n; i >>= 1;) s[i] = mp(f[i], op(s[i << 1], s[i << 1 | 1]));
  }
  S get(int i) {
    push(i);
    return s[n + i];
  }
  void set(int i, S t) {
    push(i);
    s[n + i] = t;
    pull(i);
  }
  void apply(int l, int r, F g) {
    if (l >= r) return;
    int i = l, j = r - 1;
    push(i), push(j);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ch(l++, g);
      if (r & 1) ch(--r, g);
    }
    pull(i), pull(j);
  }
  S prod(int l, int r) {
    if (l >= r) return e();
    push(l), push(r - 1);
    S lv = e(), rv = e();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, s[l++]);
      if (r & 1) rv = op(s[--r], rv);
    }
    return op(lv, rv);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, Q, K;
  cin >> N >> Q >> K;

  vi A(N);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  vc<pii> queries(Q);
  for (auto &[m, x] : queries) {
    cin >> m >> x;
    m--, x--;
  }

  vc<vi> by_m(N);
  rep(i, 0, Q) {
    auto [m, x] = queries[i];
    by_m[m].pb(i);
  }

  using S = tuple<int, int, int>;
  auto op = [&](S a, S b) -> S { return a; };
  auto e = [&]() -> S { return {0, 0, 0}; };
  using F = tuple<int, int, int>;
  auto mp = [&](F f, S x) -> S {
    auto [a1, b1, c1] = x;
    auto [a2, b2, c2] = f;
    return {a1 + a2, b1 + b2, min(c1 + b2, a1 + c2)};
  };
  auto cp = [&](F f, F g) -> F {
    auto [a1, b1, c1] = f;
    auto [a2, b2, c2] = g;
    return {a1 + a2, b1 + b2, min(c1 + b2, a1 + c2)};
  };
  auto id = [&]() -> F { return {0, 0, 0}; };
  lazy_segtree<S, op, e, F, mp, cp, id> st(N);
  vi ans(Q);
  int sum = 0;
  rep(i, 0, N) {
    sum += get<0>(st.get(A[i]));
    st.apply(max(A[i] - K, 0ll), A[i], {1, 0, 0});
    st.apply(A[i] + 1, min(A[i] + 1 + K, N), {0, 1, 0});
    for (auto j : by_m[i]) {
      auto [m, x] = queries[j];
      ans[j] = sum + get<2>(st.get(x));
    }
  }
  for (auto e : ans) {
    cout << e << '\n';
  }
}
