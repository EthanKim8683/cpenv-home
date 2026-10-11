namespace atcoder {
namespace internal {

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly_inv(std::vector<mint> &a) {
  int n = int(a.size());
  int h = internal::countr_zero((unsigned int) n);

  static const fft_info<mint> info;

  int len = h;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
  while (len) {
    if (len == 1) {
      int p = 1 << (h - len);
      mint irot = 1;
      for (int s = 0; s < (1 << (len - 1)); s++) {
        int offset = s << (h - len + 1);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p];
          a[i + offset] = l + r;
          a[i + offset + p] =
              (unsigned long long) (mint::mod() + l.val() - r.val()) *
              irot.val();
          ;
        }
        if (s + 1 != (1 << (len - 1)))
          irot *= info.irate2[countr_zero(~(unsigned int) (s))];
      }
      len--;
    } else {
      // 4-base
      int p = 1 << (h - len);
      mint irot = 1, iimag = info.iroot[2];
      for (int s = 0; s < (1 << (len - 2)); s++) {
        mint irot2 = irot * irot;
        mint irot3 = irot2 * irot;
        int offset = s << (h - len + 2);
        for (int i = 0; i < p; i++) {
          auto a0 = 1ULL * a[i + offset + 0 * p].val();
          auto a1 = 1ULL * a[i + offset + 1 * p].val();
          auto a2 = 1ULL * a[i + offset + 2 * p].val();
          auto a3 = 1ULL * a[i + offset + 3 * p].val();

          auto a2na3iimag =
              1ULL * mint((mint::mod() + a2 - a3) * iimag.val()).val();

          a[i + offset] = a0 + a1 + a2 + a3;
          a[i + offset + 1 * p] =
              (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
          a[i + offset + 2 * p] =
              (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) * irot2.val();
          a[i + offset + 3 * p] =
              (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
              irot3.val();
        }
        if (s + 1 != (1 << (len - 2)))
          irot *= info.irate3[countr_zero(~(unsigned int) (s))];
      }
      len -= 2;
    }
  }
}

}  // namespace internal
}  // namespace atcoder
