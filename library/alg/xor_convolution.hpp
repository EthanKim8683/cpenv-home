// TODO: Support for long long
template <class T, atcoder::internal::is_modint_t<T> * = nullptr>
std::vector<T> xor_convolution(std::vector<T> a, std::vector<T> b) {
  assert(a.size() == b.size());
  assert(std::popcount(a.size()) == 1);
  int n = a.size();

  fwht(a);
  fwht(b);
  for (int i = 0; i < n; i++) {
    a[i] *= b[i];
  }
  fwht(a);
  T f = (T) 1 / n;
  for (auto &e : a) {
    e *= f;
  }
  return a;
}
