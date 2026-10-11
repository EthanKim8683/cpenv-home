template <class T>
std::vector<std::vector<T>> pow(std::vector<std::vector<T>> x, long long y) {
  assert(y >= 0);
  assert(x.size() == x[0].size());
  std::vector rv(x.size(), std::vector<T>(x.size(), 0));
  for (int i = 0; i < x.size(); i++) {
    rv[i][i] = 1;
  }
  for (; y; y >>= 1, x = matmul(x, x)) {
    if (y & 1) {
      rv = matmul(x, rv);
    }
  }
  return rv;
}
