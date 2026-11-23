struct dsu {
  vi d;
  dsu(int n) : d(n, -1) {}
  int leader(int a) { return d[a] < 0 ? a : d[a] = leader(d[a]); }
  bool merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return 0;
    if (d[a] > d[b]) swap(a, b);
    d[a] += d[b], d[b] = a;
    return 1;
  }
  int size(int a) { return -d[a]; }
};
