// https://usaco.guide/plat/convex-hull?lang=cpp#with-monotone-chain
// Constructs a convex hull and returns the hull's indices in counter-clockwise
// order
// O(N\log(N))
template <class T>
std::vector<int> convex_hull(const std::vector<vec2<T>> &points) {
  std::vector<int> order(points.size());
  std::iota(order.begin(), order.end(), 0);
  std::sort(order.begin(), order.end(),
            [&](int a, int b) -> bool { return points[a] < points[b]; });

  auto area = [&](const vec2<T> &a, const vec2<T> &b, const vec2<T> &c) -> T {
    return cross(b - a, c - a);
  };

  std::vector<int> upper, lower;
  for (auto e : order) {
    while (upper.size() > 1 and area(points[upper.end()[-2]],
                                     points[upper.end()[-1]], points[e]) >= 0) {
      upper.pop_back();
    }
    upper.push_back(e);

    while (lower.size() > 1 and area(points[lower.end()[-2]],
                                     points[lower.end()[-1]], points[e]) <= 0) {
      lower.pop_back();
    }
    lower.push_back(e);
  }
  if (lower.size() <= 1) return lower;
  if (points[lower[0]] == points[lower[1]]) return {0};

  std::vector<int> rv;
  rv.insert(rv.end(), lower.begin(), lower.end());
  rv.insert(rv.end(), next(upper.rbegin()), prev(upper.rend()));
  return rv;
}
