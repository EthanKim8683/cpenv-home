vc<vi> matmul(vc<vi> a, vc<vi> b) {
  vc rv(sz(a), vi(sz(b[0]), 0));
  rep(i, 0, sz(a)) rep(j, 0, sz(b[0])) rep(k, 0, sz(a[0])) {
    rv[i][j] += a[i][k] * b[k][j];
  }
  return rv;
}
