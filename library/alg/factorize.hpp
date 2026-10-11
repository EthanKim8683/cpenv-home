template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
std::vector<T> factorize(T n) {
  if constexpr (std::is_signed_v<T>) {
    auto rv = factorize<std::make_unsigned_t<T>>(std::abs(n));
    if (n < 0) {
      rv.push_back(-1);
    }
    return reinterpret_cast<std::vector<T> &>(rv);
  } else {
    static T buffer[2 * 64];
    int l = 0, r = 0;
    buffer[r] = n;
    r++;
    std::vector<T> rv;
    while (l < r) {
      T k = buffer[l];
      l++;
      if (k < (1 << 16)) {
        while (k > 1) {
          auto p = prime_sieve(k);
          rv.push_back(p);
          k /= p;
        }
      } else if (k < (1ll << 32)) {
        int i = 0;
        while (k >= (1 << 16)) {
          auto p = trial_division(k, i);
          rv.push_back(p);
          k /= p;
        }
        while (k > 1) {
          auto p = prime_sieve(k);
          rv.push_back(p);
          k /= p;
        }
      } else {
        if (is_prime(k)) {
          rv.push_back(k);
          continue;
        }
        T x0 = 524287, c = 2147483647, f;
        do f = pollard_rho(k, x0, c++);
        while (f == k);
        buffer[r] = f;
        r++;
        buffer[r] = k / f;
        r++;
      }
    }
    return rv;
  }
}
