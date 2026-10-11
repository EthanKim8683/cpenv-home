template <class T, std::enable_if_t<std::is_integral_v<T> and
                                    std::is_unsigned_v<T>> * = nullptr>
constexpr unsigned char ilog(T n) {
  assert(n > 0);
  return bit_width(n) - 1;
}
