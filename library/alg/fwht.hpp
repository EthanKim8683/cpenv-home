// https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it
// Fast Walsh-Hadamard transform
// O(N\log(N))
template <class T, atcoder::internal::is_modint_t<T> * = nullptr>
void fwht(std::vector<T> &v) {
  assert(std::popcount(v.size()) == 1);
  int n = v.size();

  for (int k = 1; 2 * k <= n; k *= 2) {
    for (int i = 0; i < n; i += 2 * k) {
      for (int j = 0; j < k; j++) {
        T a = v[i + j], b = v[i + j + k];
        v[i + j] = a + b;
        v[i + j + k] = a - b;
      }
    }
  }
}
