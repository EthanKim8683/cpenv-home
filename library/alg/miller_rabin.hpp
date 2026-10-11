// https://cp-algorithms.com/algebra/primality_tests.html
// Primality checking using Miller-Rabin primality test
// O(\ln^2 N)
template <class T,
          std::enable_if_t<std::is_integral_v<T> and std::is_unsigned_v<T> and
                           (sizeof(T) <= 64)> * = nullptr>
bool miller_rabin(T n) {
  using T2 = double_width_t<T>;
  using UT = std::make_unsigned_t<T>;

  if (n < 2) return false;

  auto check_composite = [&](T n, T a, T d, int s) -> bool {
    T x = 1;
    for (; d; d >>= 1, a = (T2) a * a % n) {
      if (d & 1) {
        x = (T2) x * a % n;
      }
    }
    if (x == 1 or x == n - 1) return false;
    for (int i = 0; i < s - 1; i++) {
      x = (T2) x * x % n;
      if (x == n - 1) return false;
    }
    return true;
  };

  T d = n - 1;
  int s = std::countr_zero((UT) d);
  d >>= s;
  for (auto a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
    if (n == a) return true;
    if (check_composite(n, a, d, s)) return false;
  }
  return true;
}
