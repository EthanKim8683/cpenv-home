template <class S, auto op, auto e>
struct sparse_table {
  int n;
  vc<vc<S>> d;
  sparse_table(const vc<S> &v) : n(sz(v)), d(__lg(n) + 1, vc<S>(n, e())) {
    copy(all(v), d[0].begin());
    rep(i, 1, sz(d)) rep(j, 0, n - (1 << i) + 1) d[i][j] =
        op(d[i - 1][j], d[i - 1][j + (1 << (i - 1))]);
  }
  S prod(int l, int r) {
    if (l >= r) return e();
    int i = __lg(r - l);
    return op(d[i][l], d[i][r - (1 << i)]);
  }
};
