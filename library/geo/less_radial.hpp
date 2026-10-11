// https://usaco.guide/plat/sweep-line#solution---seeing-the-boundary
// Sorts vectors by angle from positive x-axis
template <class T>
struct less_radial {
  bool operator()(const vec2<T> &a, const vec2<T> &b) const {
    auto sign = [&](int x) -> int {
      if (x > 0) return 1;
      if (x < 0) return -1;
      return 0;
    };
    auto half = [&](const vec2<T> &v) -> int {
      if (sign(v.y) != 0) return sign(v.y);
      if (sign(v.x) != 0) return sign(v.x);
      assert(false);
    };
    if (half(a) != half(b)) return half(a) < half(b);
    return cross(a, b) > 0;
  }
};
