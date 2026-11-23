void ntt(vi &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vi rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    int z[] = {1, mod_pow(62, MOD >> s)};
    rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        int z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? MOD : 0);
        ai += (ai + z >= MOD ? z - MOD : z);
      }
}
vi conv(const vi &a, const vi &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = mod_pow(n, MOD - 2);
  vi L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = L[i] * R[i] % MOD * inv % MOD;
  ntt(out);
  return {out.begin(), out.begin() + s};
}
