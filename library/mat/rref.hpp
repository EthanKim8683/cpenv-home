int rref(auto &a, int vars) {
  int n = sz(a), m = sz(a[0]), r = 0;
  rep(c, 0, vars) if (r < n) {
    int p = r;
    rep(i, r, n) if (abs(a[i][c]) > abs(a[p][c])) p = i;
    if (abs(a[p][c]) < 1e-9) continue;
    swap(a[p], a[r]);
    for (int j = m; j-- > c;) a[r][j] /= a[r][c];
    rep(i, 0, n) if (i != r) for (int j = m; j-- > c;) a[i][j] -=
        a[i][c] * a[r][j];
    r++;
  }
  return r;
}
