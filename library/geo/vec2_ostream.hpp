template <class T>
std::ostream &operator<<(std::ostream &out, const vec2<T> &v) {
  out << '(' << v.x << ", " << v.y << ')';
  return out;
}
