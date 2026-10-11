template <class T>
T num_balanced_bracket_seqs(int n) {
  if (n % 2 == 1) return 0;
  return catalan<T>(n / 2);
}
