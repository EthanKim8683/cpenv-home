namespace atcoder {
namespace internal {

template <class mint, int g = internal::primitive_root<mint::mod()>,
          internal::is_static_modint_t<mint> * = nullptr>
struct fft_info {
  static constexpr int rank2 = countr_zero_constexpr(mint::mod() - 1);
  std::array<mint, rank2 + 1> root;   // root[i]^(2^i) == 1
  std::array<mint, rank2 + 1> iroot;  // root[i] * iroot[i] == 1

  std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;
  std::array<mint, std::max(0, rank2 - 2 + 1)> irate2;

  std::array<mint, std::max(0, rank2 - 3 + 1)> rate3;
  std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;

  fft_info() {
    root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
    iroot[rank2] = root[rank2].inv();
    for (int i = rank2 - 1; i >= 0; i--) {
      root[i] = root[i + 1] * root[i + 1];
      iroot[i] = iroot[i + 1] * iroot[i + 1];
    }

    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 2; i++) {
        rate2[i] = root[i + 2] * prod;
        irate2[i] = iroot[i + 2] * iprod;
        prod *= iroot[i + 2];
        iprod *= root[i + 2];
      }
    }
    {
      mint prod = 1, iprod = 1;
      for (int i = 0; i <= rank2 - 3; i++) {
        rate3[i] = root[i + 3] * prod;
        irate3[i] = iroot[i + 3] * iprod;
        prod *= iroot[i + 3];
        iprod *= root[i + 3];
      }
    }
  }
};

}  // namespace internal
}  // namespace atcoder
