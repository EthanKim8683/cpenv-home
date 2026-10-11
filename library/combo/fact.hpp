template <class T>
T fact(int n) {
  assert(n >= 0);
  auto &fact = combinatorics_cache<T>::fact;
  while (!(n < (int) fact.size())) {
    fact.push_back(fact.back() * fact.size());
  }
  return fact[n];
}
