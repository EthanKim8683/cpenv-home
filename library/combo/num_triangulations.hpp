template <class T>
T num_triangulations(int n) {
  return catalan<T>(n - 2);
}
