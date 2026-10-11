namespace atcoder {
namespace internal {

template <class mint, internal::is_static_modint_t<mint> * = nullptr>
void butterfly(std::vector<mint> &a) {
  int n = int(a.size());
  int h = internal::countr_zero((unsigned int) n);

  static const fft_info<mint> info;

  int len = 0;  // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
  while (len < h) {
    if (h - len == 1) {
      int p = 1 << (h - len - 1);
      mint rot = 1;
      for (int s = 0; s < (1 << len); s++) {
        int offset = s << (h - len);
        for (int i = 0; i < p; i++) {
          auto l = a[i + offset];
          auto r = a[i + offset + p] * rot;
          a[i + offset] = l + r;
          a[i + offset + p] = l - r;
        }
        if (s + 1 != (1 << len))
          rot *= info.rate2[countr_zero(~(unsigned int) (s))];
      }
      len++;
    } else {
      // 4-base
      int p = 1 << (h - len - 2);
      mint rot = 1, imag = info.root[2];
      for (int s = 0; s < (1 << len); s++) {
        mint rot2 = rot * rot;
        mint rot3 = rot2 * rot;
        int offset = s << (h - len);
        for (int i = 0; i < p; i++) {
          auto mod2 = 1ULL * mint::mod() * mint::mod();
          auto a0 = 1ULL * a[i + offset].val();
          auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
          auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
          auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
          auto a1na3imag = 1ULL * mint(a1 + mod2 - a3).val() * imag.val();
          auto na2 = mod2 - a2;
          a[i + offset] = a0 + a2 + a1 + a3;
          a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
          a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
          a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
        }
        if (s + 1 != (1 << len))
          rot *= info.rate3[countr_zero(~(unsigned int) (s))];
      }
      len += 2;
    }
  }
}

}  // namespace internal
}  // namespace atcoder
