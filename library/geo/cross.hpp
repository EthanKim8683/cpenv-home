template <class T>
T cross(const vec2<T> &a, const vec2<T> &b) {
  return a.x * b.y - b.x * a.y;
}
