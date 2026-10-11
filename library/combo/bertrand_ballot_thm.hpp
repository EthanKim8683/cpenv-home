template <class T>
T bertrand_ballot_thm(long long p, long long q) {
  assert(p >= 0);
  assert(q >= 0);
  if (p <= q) return 0;
  return T(p - q) / T(p + q);
}
