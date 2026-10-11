namespace atcoder {

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint> &&b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  int z = (int) internal::bit_ceil((unsigned int) (n + m - 1));
  assert((mint::mod() - 1) % z == 0);

  if (std::min(n, m) <= 60) return convolution_naive(a, b);
  return internal::convolution_fft(a, b);
}
template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution(const std::vector<mint> &a,
                              const std::vector<mint> &b) {
  int n = int(a.size()), m = int(b.size());
  if (!n || !m) return {};

  int z = (int) internal::bit_ceil((unsigned int) (n + m - 1));
  assert((mint::mod() - 1) % z == 0);

  if (std::min(n, m) <= 60) return convolution_naive(a, b);
  return internal::convolution_fft(a, b);
}

}  // namespace atcoder
