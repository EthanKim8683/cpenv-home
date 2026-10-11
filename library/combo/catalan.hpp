template <class T>
T catalan(int n) {
  if (n < 0) return 0;
  if constexpr (is_invertible_v<T>) {
    return fact<T>(2 * n) * inv_fact<T>(n + 1) * inv_fact<T>(n);
  } else {
    return fact<T>(2 * n) / (fact<T>(n + 1) * fact<T>(n));
  }
}
