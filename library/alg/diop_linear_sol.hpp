// https://cp-algorithms.com/algebra/linear-diophantine-equation.html#algorithmic-solution
// Finds solutions to ax + by = c
template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
struct diop_linear_sol {
 private:
  T xi, yi, a, b;

 public:
  diop_linear_sol(T _xi, T _yi, T _a, T _b) : xi(_xi), yi(_yi), a(_a), b(_b) {}

  T x() { return xi; }
  T y() { return yi; }

  diop_linear_sol kth_succ(T k) {
    return diop_linear_sol(xi + k * b, yi - k * a, a, b);
  }

  diop_linear_sol min_nonneg_sol_for_x() {
    int k = xi / b;
    if (xi + k * b < 0) {
      k += (xi > 0) - (xi < 0);
    }
    return kth_succ(-k);
  }

  diop_linear_sol min_nonneg_sol_for_y() {
    int k = yi / b;
    if (yi - k * b < 0) {
      k += (yi < 0) - (yi > 0);
    }
    return kth_succ(k);
  }
};
