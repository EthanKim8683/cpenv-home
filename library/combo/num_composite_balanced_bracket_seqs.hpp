// Number of balanced bracket sequences of length N composed of K non-composite
// bracket sequences
template <class T>
T num_composite_balanced_bracket_seqs(int n, int k) {
  if (n % 2 == 1) return 0;
  return bertrand_ballot_thm<T>(n / 2, n / 2 - k) * binom<T>(n - k, n / 2);
}
