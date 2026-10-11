// https://usaco.guide/plat/RURQ#implementation
// Fenwick tree with range updates
template <class T>
struct range_add_fenwick_tree {
 private:
  using T2 = double_width_t<T>;

  int n;
  std::vector<T> m;
  std::vector<T2> b;

 public:
  range_add_fenwick_tree() {}
  range_add_fenwick_tree(int _n) : n(_n), m(n + 1, 0), b(n + 1, 0) {}

  void add(int l, int r, T v) {
    assert(0 <= l and l <= r and r <= n);
    for (int i = l + 1; i <= n; i += i & -i) {
      m[i] += v;
      b[i] += (T2) v * l;
    }
    for (int i = r + 1; i <= n; i += i & -i) {
      m[i] -= v;
      b[i] -= (T2) v * r;
    }
  }

  T sum(int l, int r) {
    assert(0 <= l and l <= r and r <= n);
    T2 rv = 0;
    for (int i = l; i > 0; i -= i & -i) {
      rv -= (T2) m[i] * l - b[i];
    }
    for (int i = r; i > 0; i -= i & -i) {
      rv += (T2) m[i] * r - b[i];
    }
    return rv;
  }
};
