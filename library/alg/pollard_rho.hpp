// https://en.algorithmica.org/hpc/algorithms/factorization/#pollard-brent-algorithm
// Finds factors using Pollard's rho algorithm with Brent's optimization
// O(N^{1/4})
template <class T, std::enable_if_t<std::is_integral_v<T> and
                                    std::is_unsigned_v<T>> * = nullptr>
T pollard_rho(T n, T x = 2, T c = 1, int block_size = 1024) {
  montgomery<T> m(n);

  for (int l = block_size;; l *= 2) {
    T y = x, p = 1;
    for (int i = 0; i < l; i += block_size) {
      for (int j = 0; j < block_size; j++) {
        x = m.mul(x, x) + c;
        p = m.mul(p, (x < y ? y - x : x - y));
      }
      if (T g = std::gcd(p, n); g != 1) {
        return g;
      }
    }
  }
}
