namespace atcoder {

std::vector<long long> convolution_ll(const std::vector<long long> &a,
                                      const std::vector<long long> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  static constexpr unsigned long long MOD1 = 754974721;  // 2^24
  static constexpr unsigned long long MOD2 = 167772161;  // 2^25
  static constexpr unsigned long long MOD3 = 469762049;  // 2^26
  static constexpr unsigned long long M2M3 = MOD2 * MOD3;
  static constexpr unsigned long long M1M3 = MOD1 * MOD3;
  static constexpr unsigned long long M1M2 = MOD1 * MOD2;
  static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

  static constexpr unsigned long long i1 =
      internal::inv_gcd(MOD2 * MOD3, MOD1).second;
  static constexpr unsigned long long i2 =
      internal::inv_gcd(MOD1 * MOD3, MOD2).second;
  static constexpr unsigned long long i3 =
      internal::inv_gcd(MOD1 * MOD2, MOD3).second;

  static constexpr int MAX_AB_BIT = 24;
  static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1,
                "MOD1 isn't enough to support an array length of 2^24.");
  static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1,
                "MOD2 isn't enough to support an array length of 2^24.");
  static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1,
                "MOD3 isn't enough to support an array length of 2^24.");
  assert(n + m - 1 <= (1 << MAX_AB_BIT));

  auto c1 = convolution<MOD1>(a, b);
  auto c2 = convolution<MOD2>(a, b);
  auto c3 = convolution<MOD3>(a, b);

  std::vector<long long> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    unsigned long long x = 0;
    x += (c1[i] * i1) % MOD1 * M2M3;
    x += (c2[i] * i2) % MOD2 * M1M3;
    x += (c3[i] * i3) % MOD3 * M1M2;
    // B = 2^63, -B <= x, r(real value) < B
    // (x, x - M, x - 2M, or x - 3M) = r (mod 2B)
    // r = c1[i] (mod MOD1)
    // focus on MOD1
    // r = x, x - M', x - 2M', x - 3M' (M' = M % 2^64) (mod 2B)
    // r = x,
    //     x - M' + (0 or 2B),
    //     x - 2M' + (0, 2B or 4B),
    //     x - 3M' + (0, 2B, 4B or 6B) (without mod!)
    // (r - x) = 0, (0)
    //           - M' + (0 or 2B), (1)
    //           -2M' + (0 or 2B or 4B), (2)
    //           -3M' + (0 or 2B or 4B or 6B) (3) (mod MOD1)
    // we checked that
    //   ((1) mod MOD1) mod 5 = 2
    //   ((2) mod MOD1) mod 5 = 3
    //   ((3) mod MOD1) mod 5 = 4
    long long diff =
        c1[i] - internal::safe_mod((long long) (x), (long long) (MOD1));
    if (diff < 0) diff += MOD1;
    static constexpr unsigned long long offset[5] = {0, 0, M1M2M3, 2 * M1M2M3,
                                                     3 * M1M2M3};
    x -= offset[diff % 5];
    c[i] = x;
  }

  return c;
}

}  // namespace atcoder
