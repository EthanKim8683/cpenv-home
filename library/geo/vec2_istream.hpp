template <class T>
std::istream &operator>>(std::istream &in, vec2<T> &v) {
  in >> v.x >> v.y;
  return in;
}
