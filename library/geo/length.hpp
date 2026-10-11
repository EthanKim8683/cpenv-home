template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T length(const vec2<T> &x) {
  return std::sqrt(length2(x));
}
