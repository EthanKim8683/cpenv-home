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
};
