// https://cp-algorithms.com/algebra/primitive-root.html
// Finds a primitive root modulo n
template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
T find_primitive_root(T n) {
  if constexpr (std::is_signed_v<T>) {
    assert(n > 0);
    return find_primitive_root<std::make_unsigned_t<T>>(n);
  } else {
    if (n == 1) return 0;
    if (n == 2) return 1;

    auto primes = factorize(n - 1);
    std::sort(primes.begin(), primes.end());
    primes.erase(std::unique(primes.begin(), primes.end()), primes.end());
    for (T i = 2; i <= n; i++) {
      bool ok = true;
      for (auto p : primes) {
        if (mod_pow(i, (n - 1) / p, n) == 1) {
          ok = false;
          break;
        }
      }
      if (ok) return i;
    }
    return -1;
  }
}
