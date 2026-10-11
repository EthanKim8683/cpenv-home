// https://gist.github.com/mdickinson/e087001d213725a93eeb8d8f447a2f40
// Branchless integer square root without division
constexpr unsigned isqrt(unsigned long long n) {
  if (n == 0) return 0;

  const unsigned char lookup[128] = {
    0,   85,  83, 102, 71,  2,   36,  126, 15, 37,  28, 22,  87,  50,  107,
    46,  31,  10, 115, 57,  103, 98,  4,   33, 47,  58, 3,   118, 119, 109,
    116, 113, 63, 106, 108, 38,  120, 61,  27, 62,  79, 101, 35,  41,  104,
    13,  84,  17, 95,  53,  76,  121, 88,  34, 59,  97, 111, 5,   67,  54,
    72,  82,  52, 78,  127, 42,  44,  25,  56, 125, 91, 1,   112, 90,  99,
    105, 40,  77, 20,  81,  96,  117, 12,  70, 24,  29, 123, 94,  80,  69,
    124, 9,   8,  18,  11,  14,  64,  21,  19, 89,  7,  66,  100, 65,  48,
    26,  92,  86, 23,  114, 43,  110, 32,  74, 51,  6,  39,  93,  68,  30,
    16,  122, 60, 73,  55,  45,  75,  49,
  };

  unsigned m, k, x, b;
  int tz = std::countl_zero(n);
  n >>= tz;
  m = (unsigned) n;
  k = (unsigned) (n >> 2);
  x = lookup[k >> 1 & 127];
  x += (m * x * ~x - k) * (x - ~x);
  x += (m * x * ~x - k) * (x - ~x);
  b = m * x + 2 * k;
  b ^= -(b >> 31);
  return (b - ~b) << (tz >> 1);
}
