using BS = bitset<1000000>;
BS subset_sum_speedup_1(const vi &w) {
  map<int, int> occ;
  for (auto e : w) occ[e]++;
  BS rv;
  rv[0] = 1;
  for (auto [x, n] : occ) {
    rv |= rv << x, n--;
    if (n % 2) rv |= rv << x, n--;
    if (n) occ[2 * x] += n / 2;
  }
  return rv;
}
