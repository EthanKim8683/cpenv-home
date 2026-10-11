// https://en.algorithmica.org/hpc/number-theory/montgomery/
// https://cp-algorithms.com/algebra/montgomery_multiplication.html
// Fast modular multiplication using Montgomery space
template <class T, std::enable_if_t<std::is_integral_v<T> and
                                    std::is_unsigned_v<T>> * = nullptr>
struct montgomery {
 private:
  using T2 = double_width_t<T>;
  using TS = std::make_signed_t<T>;

  static constexpr size_t TW = 8 * sizeof(T);

  T n, nr, r2;

 public:
  constexpr montgomery(T _n) : n(_n) {
    nr = 1;
    for (int i = 1; i < TW; i *= 2) {
      nr *= 2 - n * nr;
    }
    r2 = ((T2) 1 << (TW + TW / 2)) % n;
    r2 = mul(r2, r2);
  }

  T reduce(T2 x) const {
    T q = (T) x * nr;
    TS rv = (x >> TW) - ((T2) q * n >> TW);
    if (rv < 0) {
      rv += n;
    }
    return rv;
  }

  T transform(T x) const { return mul(x, r2); }

  T mul(T x, T y) const { return reduce((T2) x * y); }
};
