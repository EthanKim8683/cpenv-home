// https://cp-algorithms.com/algebra/primitive-root.html
// Finds a primitive root modulo n
template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
bool primitive_root_exists(T n) {
  if constexpr (std::is_signed_v<T>) {
    assert(n > 0);
    return primitive_root_exists<std::make_unsigned_t<T>>(n);
  } else {
    if (n == 1 or n == 2 or n == 4) return true;

    auto primes = factorize(n % 2 == 0 ? n / 2 : n);
    for (int i = 1; i < primes.size(); i++) {
      if (primes[i] != primes[0]) return false;
    }
    return true;
  }
}
