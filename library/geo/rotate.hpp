template <class T, std::enable_if_t<std::is_floating_point_v<T>> * = nullptr>
vec2<T> rotate(const vec2<T> &v, long double theta) {
  return {v.x * std::cos(theta) - v.y * std::sin(theta),
          v.y * std::cos(theta) + v.x * std::sin(theta)};
}
