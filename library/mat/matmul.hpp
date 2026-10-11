template <class T>
std::vector<std::vector<T>> matmul(const std::vector<std::vector<T>> &a,
                                   const std::vector<std::vector<T>> &b) {
  assert(a[0].size() == b.size());
  std::vector rv(a.size(), std::vector<T>(b[0].size(), 0));
  for (int i = 0; i < a.size(); i++) {
    for (int j = 0; j < b[0].size(); j++) {
      for (int k = 0; k < a[0].size(); k++) {
        rv[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return rv;
}
