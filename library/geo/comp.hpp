// Component of a along b
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
T comp(const vec2<T> &a, const vec2<T> &b) {
  return dot(a, b) / length(b);
}
