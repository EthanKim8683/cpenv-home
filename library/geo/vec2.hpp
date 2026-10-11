template <class T>
struct vec2 {
  T x, y;

  vec2() : x(0), y(0) {}
  vec2(T x, T y) : x(x), y(y) {}
  template <class S>
  vec2(const vec2<S> &v) : x(v.x), y(v.y) {}
  vec2(const std::pair<T, T> &v) : x(v.x), y(v.y) {}

  operator std::pair<T, T>() const { return {x, y}; }

  vec2<T> operator+(const vec2<T> &rhs) const { return {x + rhs.x, y + rhs.y}; }
  vec2<T> operator-(const vec2<T> &rhs) const { return {x - rhs.x, y - rhs.y}; }
  vec2<T> operator*(T rhs) const { return {x * rhs, y * rhs}; }
  vec2<T> operator/(T rhs) const { return {x / rhs, y / rhs}; }
  vec2<T> operator-() const { return {-x, -y}; }

  friend vec2<T> operator*(T lhs, const vec2<T> &rhs) {
    return {lhs * rhs.x, lhs * rhs.y};
  }

  vec2<T> &operator+=(const vec2<T> &rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  vec2<T> &operator-=(const vec2<T> &rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
  }
  vec2<T> &operator*=(T rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
  }
  vec2<T> &operator/=(T rhs) {
    x /= rhs;
    y /= rhs;
    return *this;
  }

  bool operator==(const vec2<T> &rhs) const {
    return x == rhs.x and y == rhs.y;
  }
  bool operator<(const vec2<T> &rhs) const {
    return std::pair{x, y} < std::pair{rhs.x, rhs.y};
  }
  bool operator>(const vec2<T> &rhs) const {
    return std::pair{x, y} > std::pair{rhs.x, rhs.y};
  }
  bool operator<=(const vec2<T> &rhs) const {
    return std::pair{x, y} <= std::pair{rhs.x, rhs.y};
  }
  bool operator>=(const vec2<T> &rhs) const {
    return std::pair{x, y} >= std::pair{rhs.x, rhs.y};
  }
};
