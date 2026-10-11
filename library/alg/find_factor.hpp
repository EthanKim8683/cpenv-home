// https://en.algorithmica.org/hpc/algorithms/factorization/#further-improvements
// Factorization approach based on size of number
template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
T find_factor(T n) {
  if constexpr (std::is_signed_v<T>) {
    if (n < 0) return -1;
    return find_factor<std::make_unsigned_t<T>>(n);
  } else {
    if (n < (1 << 16)) {
      return prime_sieve(n);
    } else if (n < (1ll << 32)) {
      return trial_division(n);
    } else {
      T x0 = 524287, c = 2147483647, f;
      do f = pollard_rho(n, x0, c++);
      while (f == n);
      return f;
    }
  }
}
