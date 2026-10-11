// Projection of a onto b
template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> proj(const vec2<T> &a, const vec2<T> &b) {
  return b * dot(a, b) / dot(b, b);
}
