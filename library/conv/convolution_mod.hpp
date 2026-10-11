namespace atcoder {

template <unsigned int mod = 998244353, class T,
          std::enable_if_t<internal::is_integral<T>::value> * = nullptr>
std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  using mint = static_modint<mod>;

  int z = (int) internal::bit_ceil((unsigned int) (n + m - 1));
  assert((mint::mod() - 1) % z == 0);

  std::vector<mint> a2(n), b2(m);
  for (int i = 0; i < n; i++) {
    a2[i] = mint(a[i]);
  }
  for (int i = 0; i < m; i++) {
    b2[i] = mint(b[i]);
  }
  auto c2 = convolution(std::move(a2), std::move(b2));
  std::vector<T> c(n + m - 1);
  for (int i = 0; i < n + m - 1; i++) {
    c[i] = c2[i].val();
  }
  return c;
}

}  // namespace atcoder
