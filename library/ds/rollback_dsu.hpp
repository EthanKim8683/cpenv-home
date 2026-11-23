struct rollback_dsu {
  vi d, s;
  vc<tuple<int, int, int>> h;
  rollback_dsu(int n) : d(n, -1) {}
  int leader(int a) { return d[a] < 0 ? a : leader(d[a]); }
  bool merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return 0;
    if (d[a] > d[b]) swap(a, b);
    h.eb(a, b, d[b]);
    d[a] += d[b], d[b] = a;
    return 1;
  }
  int size(int a) { return -d[a]; }
  void save() { s.pb(sz(h)); }
  void rollback() {
    while (sz(h) > s.back()) {
      auto [a, b, x] = h.back();
      h.pop_back();
      d[b] = x, d[a] -= d[b];
    }
    s.pop_back();
  }
};
