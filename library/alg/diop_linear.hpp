template <class T, std::enable_if_t<std::is_integral_v<T>> * = nullptr>
diop_linear_sol<T> diop_linear(T a, T b, T c) {
  using U = std::make_unsigned_t<T>;

  T g, x0, y0;
  std::tie(g, x0, y0) = eegcd((U) abs(a), (U) abs(b));
  assert(c % g == 0);

  x0 *= c / g;
  y0 *= c / g;
  if (a < 0) {
    x0 = -x0;
  }
  if (b < 0) {
    y0 = -y0;
  }
  return diop_linear_sol<T>(x0, y0, a, b);
}
