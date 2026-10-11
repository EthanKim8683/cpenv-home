template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> normalize(const vec2<T> &x) {
  return x / length(x);
}
