template <class T, std::enable_if_t<is_invertible_v<T>> * = nullptr>
T inv_fact(int n) {
  assert(n >= 0);
  auto &inv_fact = combinatorics_cache<T>::inv_fact;
  while (!(n < (int) inv_fact.size())) {
    inv_fact.push_back(inv_fact.back() / inv_fact.size());
  }
  return inv_fact[n];
}
