map<int, int> occ;
for (auto e : w) occ[e]++;
bitset<1000000> b;
b[0] = 1;
for (auto [x, n] : occ) {
  b |= b << x, n--;
  if (n % 2) b |= b << x, n--;
  if (n) occ[2 * x] += n / 2;
}
