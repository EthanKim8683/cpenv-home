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
