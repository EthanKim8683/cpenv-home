auto mod_pow = [&](int x, int y) -> int {
  int rv = 1;
  for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
    if (y & 1) (rv *= x) %= MOD;
  return rv;
};
