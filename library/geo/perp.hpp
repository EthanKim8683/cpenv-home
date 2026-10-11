// Rotate 90 degrees counter-clockwise
template <class T>
vec2<T> perp(const vec2<T> &v) {
  return {-v.y, v.x};
}
