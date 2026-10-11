#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

// #define int long long
#define ll long long
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

const int MOD1 = (1ll << 31) - 1;
const int MOD2 = 1e9 + 7;
const int NIL = 1e9;

struct lazy_segtree {
  int mod;

  struct S {
    int first, hash, pow, pow_sum;
  };
  S op(S a, S b) {
    return {a.first == NIL ? b.first : a.first,
            (int) ((a.hash + (ll) a.pow * b.hash) % mod),
            (int) ((ll) a.pow * b.pow % mod),
            (int) ((a.pow_sum + (ll) a.pow * b.pow_sum) % mod)};
  }
  S e() { return {NIL, 0, 1, 0}; }
  using F = int;
  S mp(S x, F f) {
    return {(int) (((ll) x.first + f) % mod),
            (int) ((x.hash + (ll) f * x.pow_sum) % mod), x.pow, x.pow_sum};
  }
  F cp(F f, F g) { return ((ll) f + g) % mod; }
  F id() { return 0; }

  lazy_segtree() {}

  static lazy_segtree make(vi v, int base, int mod) {
    vc<S> v2(sz(v));
    rep(i, 0, sz(v)) { v2[i] = {v[i], v[i], base, 1}; }
    return lazy_segtree(v2, mod);
  }

  int query(int l, int r) {
    S s = prod(l, r);
    return (s.hash - (ll) s.first * s.pow_sum) % mod;
  }

  int lgn, n;
  vc<S> s;
  vc<F> f;
  lazy_segtree(const vc<S> &v, int _mod)
      : mod(_mod),
        lgn(__lg(2 * sz(v) - 1)),
        n(1 << lgn),
        s(2 * n),
        f(2 * n, id()) {
    rep(i, 0, sz(v)) s[n + i] = v[i];
    for (int i = n - 1; i > 0; i--) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
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

struct hasher {
  int mod, N;
  lazy_segtree st;

  hasher(vc<vi> M, int base, int _mod) : mod(_mod), N(sz(M)) {
    vi flat(N * N);
    rep(i, 0, N) {
      rep(j, 0, N) { flat[i * N + j] = M[i][j]; }
    }
    st = lazy_segtree::make(flat, base, mod);
  }

  void update(int i, int l, int r, int x) { st.apply(i * N + l, i * N + r, x); }

  int hash(int i0, int i, int l, int r) {
    int c = r - l;

    ll rv = 0;
    (rv += st.query(i * N + l, i * N + r)) %= mod;
    (rv -= st.query(i0 * N + l, i0 * N + r)) %= mod;
    (rv += mod) %= mod;
    return rv;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  mt19937 rng(time(nullptr));

  int base = rng() % MOD1;  //  % MOD2;

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vc A(N, vi(N));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vc B(N, vi(N));
    for (auto &r : B) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    hasher Ah1(A, base, MOD1);  // , Ah2(A, base, MOD2);
    hasher Bh1(B, base, MOD1);  // , Bh2(B, base, MOD2);

    while (Q--) {
      char t;
      cin >> t;

      if (t == 'U') {
        int r1, c1, r2, c2, x;
        cin >> r1 >> c1 >> r2 >> c2 >> x;
        r1--, c1--;

        rep(i, r1, r2) {
          Ah1.update(i, c1, c2, x);
          // Ah2.update(i, c1, c2, x);
        }
      } else {
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--, c1--;

        bool ok = true;
        rep(i, r1, r2) {
          ok = ok and Ah1.hash(r1, i, c1, c2) == Bh1.hash(r1, i, c1, c2);
          // ok = ok and Ah2.hash(r1, i, c1, c2) == Bh2.hash(r1, i, c1, c2);
        }
        cout << (ok ? "Yes" : "No") << '\n';
      }
    }
  }
}
