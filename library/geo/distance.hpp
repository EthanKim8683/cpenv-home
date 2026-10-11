template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T distance(const vec2<T> &a, const vec2<T> &b) {
  return length(b - a);
}
