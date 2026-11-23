struct fenwick_tree {
  int n;
  vi d;
  fenwick_tree(int _n) : n(_n + 1), d(n, 0) {}
  void add(int i, int x) {
    for (i++; i < n; i += i & -i) d[i] += x;
  }
  int sum(int i) {
    int rv = 0;
    for (; i; i -= i & -i) rv += d[i];
    return rv;
  }
  int lower_bound(int x) {
    if (x <= 0) return -1;
    int i = 0;
    for (int j = 1 << __lg(n); j; j >>= 1)
      if (i + j < n and d[i + j] < x) i += j, x -= d[i];
    return i;
  }
};
