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
    s[i] = mp(s[i], g);
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
    for (i += n; i >>= 1;) s[i] = mp(op(s[i << 1], s[i << 1 | 1]), f[i]);
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

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) cin >> e;

    vi index(N + 1);
    rep(i, 0, N) { index[P[i]] = i; }

    using S = int;
    auto op = [&](S a, S b) -> S { return max(a, b); };
    auto e = [&]() -> S { return 0; };
    using F = int;
    auto mp = [&](F f, S x) -> S { return x + f; };
    auto cp = [&](F f, F g) -> F { return f + g; };
    auto id = [&]() -> F { return 0; };
    lazy_segtree<S, op, e, F, mp, cp, id> st(2 * N);
    rep(i, 1, N) {
      int l = index[i], r = index[i + 1];
      if (l > r) {
        swap(l, r);
      }
      st.apply(l, r, 1);
    }
    st.apply(index[1], 2 * N, 1);
    st.apply(index[N], 2 * N, 1);

    int ans = 0;
    rep(i, 0, N) {
      if (st.prod(i, i + N) <= 4) {
        ans += 1;
      }

      if (P[i] == 1) {
        st.apply(i, 2 * N, -1);
        st.apply(i + N, 2 * N, 1);
      } else {
        int j = index[P[i] - 1];
        if (j < i) {
          st.apply(i, j + N, -1);
          st.apply(j + N, i + N, 1);
        } else {
          st.apply(i, j, -1);
          st.apply(j, i + N, 1);
        }
      }

      if (P[i] == N) {
        st.apply(i, 2 * N, -1);
        st.apply(i + N, 2 * N, 1);
      } else {
        int j = index[P[i] + 1];
        if (j < i) {
          st.apply(i, j + N, -1);
          st.apply(j + N, i + N, 1);
        } else {
          st.apply(i, j, -1);
          st.apply(j, i + N, 1);
        }
      }
    }
    cout << ans << '\n';
  }
}
