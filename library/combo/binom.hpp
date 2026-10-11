template <class T>
T binom(int n, int k) {
  if (n < 0 or n - k < 0 or k < 0) return 0;
  if constexpr (is_invertible_v<T>) {
    return fact<T>(n) * inv_fact<T>(n - k) * inv_fact<T>(k);
  } else {
    return fact<T>(n) / (fact<T>(n - k) * fact<T>(k));
  }
}
