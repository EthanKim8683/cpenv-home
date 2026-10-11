template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
bool is_prime(T n) {
  if constexpr (std::is_signed_v<T>) {
    if (!(n > 1)) return false;
    return is_prime<std::make_unsigned_t<T>>(n);
  } else {
    return miller_rabin(n);
  }
}
