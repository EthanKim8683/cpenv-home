inline uint64_t rng() {
  static uint64_t x = 88172645463325252ULL;
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  return x * 0x2545F4914F6CDD1DULL;
}

inline uint32_t rng(uint32_t n) { return ((rng() >> 32) * n) >> 32; }
