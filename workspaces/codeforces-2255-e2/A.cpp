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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

template <class S, auto op, auto e, class F, auto mp, auto cp, auto id>
struct lazy_segtree {
  int lgn, n;
  vc<S> s;
  vc<F> f;
  lazy_segtree(const vc<S> &v)
      : lgn(__lg(2 * sz(v) - 1)), n(1 << lgn), s(2 * n), f(2 * n, id()) {
    rep(i, 0, sz(v)) s[n + i] = v[i];
    // for (int i = n - 1; i > 0; i--) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  lazy_segtree(int m) : lazy_segtree(vc(m, e())) {}
  void ch(int i, const F &g) {
    if (i >= n) {
      s[i] = mp(g, s[i]);
    }
    if (i < n) f[i] = cp(f[i], g);
  }
  void push(int i) {
    for (int j = lgn; j > 0; j--) {
      int k = (i + n) >> j;
      if (f[k].id) continue;
      ch(k << 1, f[k]);
      ch(k << 1 | 1, f[k]);
      f[k] = id();
    }
  }
  // void pull(int i) {
  //   for (i += n; i >>= 1;) s[i] = mp(f[i], op(s[i << 1], s[i << 1 | 1]));
  // }
  S get(int i) {
    push(i);
    return s[n + i];
  }
  void set(int i, S t) {
    push(i);
    s[n + i] = t;
    // pull(i);
  }
  void apply(int l, int r, const F &g) {
    if (l >= r) return;
    int i = l, j = r - 1;
    push(i), push(j);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) ch(l++, g);
      if (r & 1) ch(--r, g);
    }
    // pull(i), pull(j);
  }
  // S prod(int l, int r) {
  //   if (l >= r) return e();
  //   push(l), push(r - 1);
  //   S lv = e(), rv = e();
  //   for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
  //     if (l & 1) lv = op(lv, s[l++]);
  //     if (r & 1) rv = op(s[--r], rv);
  //   }
  //   return op(lv, rv);
  // }
};

int sign(int x) { return (x > 0) - (x < 0); }

int safe_mul(int a, int b) {
  if (abs(a) == INF or abs(b) == INF) {
    return sign(a) * sign(b) * INF;
  }
  return a * b;
}

struct S {
  int ps, min_ps, max_sum, value;
};
S op(const S &a, const S &b) { return {}; };
S e() { return {}; };
struct F {
  bool id;
  int neg_ps, neg_min_ps, neg_max_ps, neg_max_sum, neg_value;
  int pos_ps, pos_min_ps, pos_max_ps, pos_max_sum, pos_value;
  bool replace;
  int replace_ps, replace_min_ps, replace_max_ps, replace_max_sum,
      replace_value;
};
S mp(const F &f, const S &x) {
  if (f.id) return x;

  int f_ps, f_min_ps, f_max_ps, f_max_sum, f_value;
  if (x.value < 0) {
    f_ps = safe_mul(x.value, f.neg_ps);
    f_min_ps = safe_mul(x.value, f.neg_min_ps);
    f_max_ps = safe_mul(x.value, f.neg_max_ps);
    f_max_sum = safe_mul(x.value, f.neg_max_sum);
    f_value = safe_mul(x.value, f.neg_value);
  } else {
    f_ps = safe_mul(x.value, f.pos_ps);
    f_min_ps = safe_mul(x.value, f.pos_min_ps);
    f_max_ps = safe_mul(x.value, f.pos_max_ps);
    f_max_sum = safe_mul(x.value, f.pos_max_sum);
    f_value = safe_mul(x.value, f.pos_value);
  }

  S y;
  y.ps = x.ps + f_ps;

  y.min_ps = INF;
  chmin(y.min_ps, x.min_ps);
  chmin(y.min_ps, x.ps + f_min_ps);

  y.max_sum = -INF;
  chmax(y.max_sum, x.max_sum);
  chmax(y.max_sum, f_max_sum);
  chmax(y.max_sum, (x.ps + f_max_ps) - x.min_ps);

  y.value = f_value;
  if (!f.replace) return y;

  S z;
  z.ps = y.ps + f.replace_ps;

  z.min_ps = INF;
  chmin(z.min_ps, y.min_ps);
  chmin(z.min_ps, y.ps + f.replace_min_ps);

  z.max_sum = -INF;
  chmax(z.max_sum, y.max_sum);
  chmax(z.max_sum, f.replace_max_sum);
  chmax(z.max_sum, (y.ps + f.replace_max_ps) - y.min_ps);

  z.value = f.replace_value;
  return z;
};
F cp(const F &f, const F &g) {
  if (f.id) return g;
  if (g.id) return f;

  F h;
  if (f.replace) {
    int g_ps, g_min_ps, g_max_ps, g_max_sum, g_value;
    if (f.replace_value < 0) {
      g_ps = safe_mul(f.replace_value, g.neg_ps);
      g_min_ps = safe_mul(f.replace_value, g.neg_min_ps);
      g_max_ps = safe_mul(f.replace_value, g.neg_max_ps);
      g_max_sum = safe_mul(f.replace_value, g.neg_max_sum);
      g_value = safe_mul(f.replace_value, g.neg_value);
    } else {
      g_ps = safe_mul(f.replace_value, g.pos_ps);
      g_min_ps = safe_mul(f.replace_value, g.pos_min_ps);
      g_max_ps = safe_mul(f.replace_value, g.pos_max_ps);
      g_max_sum = safe_mul(f.replace_value, g.pos_max_sum);
      g_value = safe_mul(f.replace_value, g.pos_value);
    }

    h.neg_ps = f.neg_ps;
    h.neg_min_ps = f.neg_min_ps;
    h.neg_max_ps = f.neg_max_ps;
    h.neg_max_sum = f.neg_max_sum;
    h.neg_value = f.neg_value;
    h.pos_ps = f.pos_ps;
    h.pos_min_ps = f.pos_min_ps;
    h.pos_max_ps = f.pos_max_ps;
    h.pos_max_sum = f.pos_max_sum;
    h.pos_value = f.pos_value;
    h.replace = true;
    h.replace_ps = f.replace_ps + g_ps;

    h.replace_min_ps = INF;
    chmin(h.replace_min_ps, f.replace_min_ps);
    chmin(h.replace_min_ps, f.replace_ps + g_min_ps);

    h.replace_max_ps = -INF;
    chmax(h.replace_max_ps, f.replace_max_ps);
    chmax(h.replace_max_ps, f.replace_ps + g_max_ps);

    h.replace_max_sum = -INF;
    chmax(h.replace_max_sum, f.replace_max_sum);
    chmax(h.replace_max_sum, g_max_sum);
    chmax(h.replace_max_sum, (f.replace_ps + g_max_ps) - f.replace_min_ps);

    h.replace_value = g_value;
  } else {
    int g_neg_ps, g_neg_min_ps, g_neg_max_ps, g_neg_max_sum, g_neg_value;
    if (f.neg_value > 0) {
      g_neg_ps = safe_mul(f.neg_value, g.neg_ps);
      g_neg_min_ps = safe_mul(f.neg_value, g.neg_min_ps);
      g_neg_max_ps = safe_mul(f.neg_value, g.neg_max_ps);
      g_neg_max_sum = safe_mul(f.neg_value, g.neg_max_sum);
      g_neg_value = safe_mul(f.neg_value, g.neg_value);
    } else {
      g_neg_ps = safe_mul(f.neg_value, g.pos_ps);
      g_neg_min_ps = safe_mul(f.neg_value, g.pos_min_ps);
      g_neg_max_ps = safe_mul(f.neg_value, g.pos_max_ps);
      g_neg_max_sum = safe_mul(f.neg_value, g.pos_max_sum);
      g_neg_value = safe_mul(f.neg_value, g.pos_value);
    }

    h.neg_ps = f.neg_ps + g_neg_ps;

    h.neg_min_ps = -INF;
    chmax(h.neg_min_ps, f.neg_min_ps);
    chmax(h.neg_min_ps, f.neg_ps + g_neg_min_ps);

    h.neg_max_ps = INF;
    chmin(h.neg_max_ps, f.neg_max_ps);
    chmin(h.neg_max_ps, f.neg_ps + g_neg_max_ps);

    h.neg_max_sum = INF;
    chmin(h.neg_max_sum, f.neg_max_sum);
    chmin(h.neg_max_sum, g_neg_max_sum);
    chmin(h.neg_max_sum, (f.neg_ps + g_neg_max_ps) - f.neg_min_ps);

    h.neg_value = g_neg_value;

    int g_pos_ps, g_pos_min_ps, g_pos_max_ps, g_pos_max_sum, g_pos_value;
    if (f.pos_value < 0) {
      g_pos_ps = safe_mul(f.pos_value, g.neg_ps);
      g_pos_min_ps = safe_mul(f.pos_value, g.neg_min_ps);
      g_pos_max_ps = safe_mul(f.pos_value, g.neg_max_ps);
      g_pos_max_sum = safe_mul(f.pos_value, g.neg_max_sum);
      g_pos_value = safe_mul(f.pos_value, g.neg_value);
    } else {
      g_pos_ps = safe_mul(f.pos_value, g.pos_ps);
      g_pos_min_ps = safe_mul(f.pos_value, g.pos_min_ps);
      g_pos_max_ps = safe_mul(f.pos_value, g.pos_max_ps);
      g_pos_max_sum = safe_mul(f.pos_value, g.pos_max_sum);
      g_pos_value = safe_mul(f.pos_value, g.pos_value);
    }

    h.pos_ps = f.pos_ps + g_pos_ps;

    h.pos_min_ps = INF;
    chmin(h.pos_min_ps, f.pos_min_ps);
    chmin(h.pos_min_ps, f.pos_ps + g_pos_min_ps);

    h.pos_max_ps = -INF;
    chmax(h.pos_max_ps, f.pos_max_ps);
    chmax(h.pos_max_ps, f.pos_ps + g_pos_max_ps);

    h.pos_max_sum = -INF;
    chmax(h.pos_max_sum, f.pos_max_sum);
    chmax(h.pos_max_sum, g_pos_max_sum);
    chmax(h.pos_max_sum, (f.pos_ps + g_pos_max_ps) - f.pos_min_ps);

    h.pos_value = g_pos_value;
    h.replace = false;
  }
  if (!g.replace) return h;

  F j;
  if (h.replace) {
    j.neg_ps = h.neg_ps;
    j.neg_min_ps = h.neg_min_ps;
    j.neg_max_ps = h.neg_max_ps;
    j.neg_max_sum = h.neg_max_sum;
    j.neg_value = h.neg_value;
    j.pos_ps = h.pos_ps;
    j.pos_min_ps = h.pos_min_ps;
    j.pos_max_ps = h.pos_max_ps;
    j.pos_max_sum = h.pos_max_sum;
    j.pos_value = h.pos_value;
    j.replace = true;
    j.replace_ps = h.replace_ps + g.replace_ps;

    j.replace_min_ps = INF;
    chmin(j.replace_min_ps, h.replace_min_ps);
    chmin(j.replace_min_ps, h.replace_ps + g.replace_min_ps);

    j.replace_max_ps = -INF;
    chmax(j.replace_max_ps, h.replace_max_ps);
    chmax(j.replace_max_ps, h.replace_ps + g.replace_max_ps);

    j.replace_max_sum = -INF;
    chmax(j.replace_max_sum, h.replace_max_sum);
    chmax(j.replace_max_sum, g.replace_max_sum);
    chmax(j.replace_max_sum,
          (h.replace_ps + g.replace_max_ps) - h.replace_min_ps);

    j.replace_value = g.replace_value;
  } else {
    j.neg_ps = h.neg_ps;
    j.neg_min_ps = h.neg_min_ps;
    j.neg_max_ps = h.neg_max_ps;
    j.neg_max_sum = h.neg_max_sum;
    j.neg_value = h.neg_value;
    j.pos_ps = h.pos_ps;
    j.pos_min_ps = h.pos_min_ps;
    j.pos_max_ps = h.pos_max_ps;
    j.pos_max_sum = h.pos_max_sum;
    j.pos_value = h.pos_value;
    j.replace = true;
    j.replace_ps = g.replace_ps;
    j.replace_min_ps = g.replace_min_ps;
    j.replace_max_ps = g.replace_max_ps;
    j.replace_max_sum = g.replace_max_sum;
    j.replace_value = g.replace_value;
  }
  return j;
};
F id() {
  F f;
  f.id = true;
  f.neg_ps = 0;
  f.neg_min_ps = 0;
  f.neg_max_ps = INF;
  f.neg_max_sum = INF;
  f.neg_value = 1;
  f.pos_ps = 0;
  f.pos_min_ps = 0;
  f.pos_max_ps = -INF;
  f.pos_max_sum = -INF;
  f.pos_value = 1;
  f.replace = false;
  return f;
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // seg maintains:
  // - ps
  // - min ps
  // - max subarray sum
  // - whether pos or neg
  //
  // lazy maintains (as a function of pos/neg):
  // - ps - (prev ps)
  // - max ps - (prev ps)
  // - min ps - (prev ps)
  // - max subarray sum on lazy
  // - whether final is pos or neg
  //
  // basically all lazy updates
  //
  // i think this might be enough
  //
  // merging lazy and lazy:
  // ps: ps1+ps2
  // maxps: max(maxps1, ps1+maxps2)
  // minps: min(minps1, ps1+minps2)
  // maxsum: max(maxsum1, maxsum2, (ps1+maxps2)-minps1)
  // sign: sign2[sign1[given]]
  //
  // merging seg and lazy:
  // ps: ps1+ps2
  // minps: min(minps1, ps1+minps2)
  // maxsum: max(maxsum1, maxsum2, (ps1+maxps2)-minps1)
  // sign: sign2[sign1]
  //
  // op 1 to lazy:
  // ps: x
  // maxps: max(x, 0)
  // minps: min(x, 0)
  // maxsum: max(x, 0)
  // sign: x
  //
  // op 2 to lazy:
  // ps: -given
  // maxps: max(-given, 0)
  // ...
  //
  // null op to lazy:
  // ps: given
  // ...
  //
  // ident:
  // ps: 0
  // minps: 0
  // maxps: 0
  // maxsum: 0
  // sign: given
  //
  //
  // OKAY E2 TIME
  //
  //
  // i think we can't directly map signs, however, we can have a replace bool
  // because the other case is just sign change
  //
  // replacement can be thought of as always after sign changing phase
  //
  // so have sign change values (dependent on original), then replacement values

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto encode = [&](int x) -> int { return x + 1; };

    auto decode = [&](int x) -> int { return x - 1; };

    vc<S> init(N);
    rep(i, 0, N) {
      init[i].ps = A[i];
      init[i].min_ps = min(A[i], 0ll);
      init[i].max_sum = A[i];
      init[i].value = A[i];
    }
    lazy_segtree<S, op, e, F, mp, cp, id> st(init);

    int ans = 0;
    auto d = [&](int y) -> int { return (y ^ ans) % N + 1; };

    F f_null;
    f_null.id = false;
    f_null.neg_ps = 1;
    f_null.neg_min_ps = 1;
    f_null.neg_max_ps = 1;
    f_null.neg_max_sum = 1;
    f_null.neg_value = 1;
    f_null.pos_ps = 1;
    f_null.pos_min_ps = 0;
    f_null.pos_max_ps = 1;
    f_null.pos_max_sum = 1;
    f_null.pos_value = 1;
    f_null.replace = false;

    // cerr << "values: ";
    // rep(i, 0, N) { cerr << st.get(i).value << ' '; }
    // cerr << '\n';
    // cerr << "ps: ";
    // rep(i, 0, N) { cerr << st.get(i).ps << ' '; }
    // cerr << '\n';

    while (Q--) {
      int t;
      cin >> t;

      if (t == 1) {
        unsigned int u, v;
        int x;
        cin >> u >> v >> x;

        int l = min(d(u), d(v)), r = max(d(u), d(v));
        l--;
        // cerr << "query: 1 " << l << ' ' << r << ' ' << x << '\n';

        F f_op;
        f_op.id = false;
        f_op.neg_ps = 0;
        f_op.neg_min_ps = 0;
        f_op.neg_max_ps = INF;
        f_op.neg_max_sum = INF;
        f_op.neg_value = 1;
        f_op.pos_ps = 0;
        f_op.pos_min_ps = 0;
        f_op.pos_max_ps = -INF;
        f_op.pos_max_sum = -INF;
        f_op.pos_value = 1;
        f_op.replace = true;
        f_op.replace_ps = x;
        f_op.replace_min_ps = max(x, 0ll);
        f_op.replace_max_ps = x;
        f_op.replace_max_sum = x;
        f_op.replace_value = x;

        st.apply(0, l, f_null);
        st.apply(l, r, f_op);
        st.apply(r, N, f_null);
      } else if (t == 2) {
        unsigned int u, v;
        cin >> u >> v;

        int l = min(d(u), d(v)), r = max(d(u), d(v));
        l--;
        // cerr << "query: 2 " << l << ' ' << r << '\n';

        F f_op;
        f_op.id = false;
        f_op.neg_ps = -1;
        f_op.neg_min_ps = 0;
        f_op.neg_max_ps = -1;
        f_op.neg_max_sum = -1;
        f_op.neg_value = -1;
        f_op.pos_ps = -1;
        f_op.pos_min_ps = -1;
        f_op.pos_max_ps = -1;
        f_op.pos_max_sum = -1;
        f_op.pos_value = -1;
        f_op.replace = false;

        st.apply(0, l, f_null);
        st.apply(l, r, f_op);
        st.apply(r, N, f_null);
      } else if (t == 3) {
        unsigned int u, v;
        cin >> u >> v;

        int l = min(d(u), d(v)), r = max(d(u), d(v));
        l--;
        // cerr << "query: 3 " << l << ' ' << r << '\n';

        F f_op;
        f_op.id = false;
        f_op.neg_ps = 0;
        f_op.neg_min_ps = 0;
        f_op.neg_max_ps = 0;
        f_op.neg_max_sum = 0;
        f_op.neg_value = 0;
        f_op.pos_ps = 1;
        f_op.pos_min_ps = 0;
        f_op.pos_max_ps = 1;
        f_op.pos_max_sum = 1;
        f_op.pos_value = 1;
        f_op.replace = false;

        st.apply(0, l, f_null);
        st.apply(l, r, f_op);
        st.apply(r, N, f_null);
      } else {
        unsigned int u;
        cin >> u;

        int p = d(u);
        p--;
        // cerr << "query: 4 " << p << '\n';

        ans = st.get(p).max_sum;
        cout << ans << '\n';

        st.apply(0, N, f_null);
      }

      // cerr << "values: ";
      // rep(i, 0, N) { cerr << st.get(i).value << ' '; }
      // cerr << '\n';
      // cerr << "ps: ";
      // rep(i, 0, N) { cerr << st.get(i).ps << ' '; }
      // cerr << '\n';
    }
  }
}
