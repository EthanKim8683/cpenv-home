int mod_pow(int a, int b, int m = MOD) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}
