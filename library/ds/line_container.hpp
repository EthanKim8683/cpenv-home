// https://usaco.guide/adv/line-container?lang=cpp#example-problem
template <class T, class Compare = std::less<T>,
          std::enable_if_t<std::is_arithmetic_v<T>> * = nullptr>
struct line_container {
 private:
  static constexpr Compare comp{};
  static constexpr T inf = std::is_integral_v<T>
                               ? std::numeric_limits<T>::max()
                               : std::numeric_limits<T>::infinity();

  struct line {
    T m, b;
    mutable T x;
    bool operator<(const line &rhs) const { return comp(rhs.m, m); };
    bool operator<(T rhs) const { return x < rhs; };
  };

  std::set<line, std::less<>> lines;

  static T divide(T x, T y) {
    if constexpr (std::is_integral_v<T>) {
      T rv = x / y;
      if (x % y != 0 and (x > 0) != (y > 0)) {
        rv -= 1;
      }
      return rv;
    } else {
      return x / y;
    }
  }

  static T intersect(std::set<line>::iterator it1,
                     std::set<line>::iterator it2) {
    return divide(it1->b - it2->b, it2->m - it1->m);
  }

  bool should_erase(std::set<line>::iterator it) {
    if (it == lines.begin()) return false;
    if (next(it) == lines.end()) return false;
    return intersect(it, next(it)) <= intersect(prev(it), it);
  }

 public:
  void insert(T m, T b) {
    auto it = lines.find({m});
    if (it != lines.end()) {
      if (!comp(b, it->b)) return;
      lines.erase(it);
    }
    it = lines.emplace(m, b, inf).first;
    if (should_erase(it)) {
      lines.erase(it);
    } else {
      while (it != lines.begin() and should_erase(prev(it))) {
        lines.erase(prev(it));
      }
      while (next(it) != lines.end() and should_erase(next(it))) {
        lines.erase(next(it));
      }
      if (it != lines.begin()) {
        prev(it)->x = intersect(prev(it), it);
      }
      if (next(it) != lines.end()) {
        it->x = intersect(it, next(it));
      }
    }
  }

  T get(T x) {
    auto it = lines.lower_bound(x);
    return it->m * x + it->b;
  }
};
