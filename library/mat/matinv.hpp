bool matinv(auto &a) {
  int n = sz(a);
  rep(i, 0, n) a[i].resize(2 * n), a[i][n + i] = 1;
  if (rref(a, n) < n) return 0;
  rep(i, 0, n) a[i].erase(begin(a[i]), begin(a[i]) + n);
  return 1;
}
