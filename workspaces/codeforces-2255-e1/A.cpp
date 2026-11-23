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
      if (f[k].max_sum[0] == -INF) continue;
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

struct S {
  int ps, min_ps, max_sum, sign;
};
S op(const S &a, const S &b) { return {}; };
S e() { return {}; };
struct F {
  int ps[3], min_ps[3], max_ps[3], max_sum[3], sign[3];
};
S mp(const F &f, const S &x) {
  S y;
  int j = x.sign;
  y.ps = x.ps + f.ps[j];
  y.min_ps = min(x.min_ps, x.ps + f.min_ps[j]);
  y.max_sum =
      max(x.max_sum, max(f.max_sum[j], (x.ps + f.max_ps[j]) - x.min_ps));
  y.sign = f.sign[j];
  return y;
};
F cp(const F &f, const F &g) {
  F fg;
  rep(i, 0, 3) {
    int j = f.sign[i];
    fg.ps[i] = f.ps[i] + g.ps[j];
    fg.max_ps[i] = max(f.max_ps[i], f.ps[i] + g.max_ps[j]);
    fg.min_ps[i] = min(f.min_ps[i], f.ps[i] + g.min_ps[j]);
    fg.max_sum[i] = max(
        f.max_sum[i], max(g.max_sum[j], (f.ps[i] + g.max_ps[j]) - f.min_ps[i]));
    fg.sign[i] = g.sign[j];
  }
  return fg;
};
F id() {
  F fg;
  rep(i, 0, 3) {
    fg.ps[i] = 0;
    fg.max_ps[i] = -INF;
    fg.min_ps[i] = 0;
    fg.max_sum[i] = -INF;
    fg.sign[i] = i;
  }
  return fg;
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

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
      init[i].sign = encode(A[i]);
    }
    lazy_segtree<S, op, e, F, mp, cp, id> st(init);

    int ans = 0;
    auto d = [&](int y) -> int { return (y ^ ans) % N + 1; };

    auto from_mapping = [&](int mp[3]) -> F {
      F f;
      rep(i, 0, 3) {
        int x = mp[i];
        f.ps[i] = x;
        f.max_ps[i] = x;
        f.min_ps[i] = min(x, 0ll);
        f.max_sum[i] = x;
        f.sign[i] = encode(x);
      }
      return f;
    };

    F f_null = from_mapping((int[]) {-1, 0, 1});

    // cerr << "values: ";
    // rep(i, 0, N) { cerr << decode(st.get(i).sign) << ' '; }
    // cerr << '\n';
    // cerr << "ps: ";
    // rep(i, 0, N) { cerr << st.get(i).max_sum << ' '; }
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

        F f_op = from_mapping((int[]) {x, x, x});
        st.apply(0, l, f_null);
        st.apply(l, r, f_op);
        st.apply(r, N, f_null);
      } else if (t == 2) {
        unsigned int u, v;
        cin >> u >> v;

        int l = min(d(u), d(v)), r = max(d(u), d(v));
        l--;
        // cerr << "query: 2 " << l << ' ' << r << '\n';

        F f_op = from_mapping((int[]) {1, 0, -1});
        st.apply(0, l, f_null);
        st.apply(l, r, f_op);
        st.apply(r, N, f_null);
      } else if (t == 3) {
        unsigned int u, v;
        cin >> u >> v;

        int l = min(d(u), d(v)), r = max(d(u), d(v));
        l--;
        // cerr << "query: 3 " << l << ' ' << r << '\n';

        F f_op = from_mapping((int[]) {0, 0, 1});
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
      // rep(i, 0, N) { cerr << decode(st.get(i).sign) << ' '; }
      // cerr << '\n';
      // cerr << "ps: ";
      // rep(i, 0, N) { cerr << st.get(i).ps << ' '; }
      // cerr << '\n';
    }
  }
}
