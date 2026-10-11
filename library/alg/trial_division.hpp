unsigned int trial_division(unsigned int n, int &i) {
  for (auto p : fp.magic_primes) {
    if (p * n < p) return (unsigned long long) -1 / p + 1;
  }
  return 1;
}
unsigned int trial_division(unsigned int n) {
  int i;
  return trial_division(n, i);
}
