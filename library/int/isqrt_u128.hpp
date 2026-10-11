// https://scicomp.stackexchange.com/a/36163
constexpr unsigned long long isqrt(unsigned __int128 n) {
  if (n == 0) return 0;

  const unsigned long long lookup[32] = {
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x85ffffffffffffffULL,
    0x8cffffffffffffffULL, 0x94ffffffffffffffULL, 0x9affffffffffffffULL,
    0xa1ffffffffffffffULL, 0xa7ffffffffffffffULL, 0xadffffffffffffffULL,
    0xb3ffffffffffffffULL, 0xb9ffffffffffffffULL, 0xbeffffffffffffffULL,
    0xc4ffffffffffffffULL, 0xc9ffffffffffffffULL, 0xceffffffffffffffULL,
    0xd3ffffffffffffffULL, 0xd8ffffffffffffffULL, 0xdcffffffffffffffULL,
    0xe1ffffffffffffffULL, 0xe6ffffffffffffffULL, 0xeaffffffffffffffULL,
    0xeeffffffffffffffULL, 0xf3ffffffffffffffULL, 0xf7ffffffffffffffULL,
    0xfbffffffffffffffULL, 0xffffffffffffffffULL};

  int lz = countl_zero(n), i = n << (lz & ~1) >> 123;
  unsigned long long y = lookup[i] >> (lz >> 1), hi = n >> 64, q;

  q = 0xffffffffffffffffULL;
  if (hi < y) q = n / y;
  y = (y + q) / 2;
  if (lz < 106) {
    q = 0xffffffffffffffffULL;
    if (hi < y) q = n / y;
    y = (y + q) / 2;
    if (lz < 86) {
      q = 0xffffffffffffffffULL;
      if (hi < y) q = n / y;
      y = (y + q) / 2;
      if (lz < 42) {
        q = 0xffffffffffffffffULL;
        if (hi < y) q = n / y;
        y = (y + q) / 2;
      }
    }
  }
  if ((unsigned __int128) y * y > n) y--;
  return y;
}
