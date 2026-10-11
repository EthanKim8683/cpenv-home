template <class T>
T bertrand_ballot_thm_with_ties(long long p, long long q) {
  assert(p >= 0);
  assert(q >= 0);
  if (p < q) return 0;
  return T(p + 1 - q) / T(p + 1);
}
