vc<vi> matpow(vc<vi> x, int y) {
  vc rv(sz(x), vi(sz(x), 0));
  rep(i, 0, sz(x)) rv[i][i] = 1;
  for (; y; y >>= 1, x = matmul(x, x))
    if (y & 1) rv = matmul(rv, x);
  return rv;
}
