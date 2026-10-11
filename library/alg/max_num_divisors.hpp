// https://ideone.com/JNRMsQ
// Finds the maximum number of divisors of any number at most n and the number
// with the maximum number of divisors
std::pair<unsigned long long, unsigned long long> max_num_divisors(
    unsigned long long n) {
  using T2 = double_width_t<unsigned long long>;

  int primes[] = {2,  3,  5,  7,  11, 13, 17, 19, 23, 29, 31,
                  37, 41, 43, 47, 51, 53, 59, 61, 67, 71};

  std::pair<unsigned long long, unsigned long long> rv = {0, 0};
  auto dfs = [&](auto self, int i, int jmax, unsigned long long x,
                 unsigned long long count) -> void {
    rv = max(rv, {count, x});
    if (i == (int) std::size(primes)) return;

    for (int j = 1; j <= jmax; j++) {
      T2 x2 = (T2) x * primes[i];
      if (x2 > n) return;
      x = x2;
      self(self, i + 1, j, x, count * (j + 1));
    }
  };
  dfs(dfs, 0, 64, 1, 1);
  return rv;
}
template <class T>
std::pair<T, T> max_num_divisors(T x) {
  return max_num_divisors((unsigned long long) x);
}
