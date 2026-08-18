void rsos(vi &v, bool sup = 0) {
  for (int i = sz(v); i--;)
    for (int j = 1 << sz(v); j--;)
      if ((j >> i & 1) ^ sup) v[j] -= v[j - (1 << i)];
}
