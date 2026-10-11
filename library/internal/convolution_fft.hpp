namespace atcoder {
namespace internal {

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
  int n = int(a.size()), m = int(b.size());
  int z = (int) internal::bit_ceil((unsigned int) (n + m - 1));
  a.resize(z);
  internal::butterfly(a);
  b.resize(z);
  internal::butterfly(b);
  for (int i = 0; i < z; i++) {
    a[i] *= b[i];
  }
  internal::butterfly_inv(a);
  a.resize(n + m - 1);
  mint iz = mint(z).inv();
  for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
  return a;
}

}  // namespace internal
}  // namespace atcoder
