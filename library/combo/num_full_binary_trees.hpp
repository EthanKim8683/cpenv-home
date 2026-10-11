template <class T>
T num_full_binary_trees(int n) {
  if (n % 2 == 0) return 0;
  return catalan<T>(n / 2);
}
