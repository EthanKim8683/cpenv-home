namespace atcoder {
namespace internal {

// @param n `1 <= n`
// @return same with std::bit::countr_zero
constexpr int countr_zero_constexpr(unsigned int n) {
  int x = 0;
  while (!(n & (1 << x))) x++;
  return x;
}

}  // namespace internal
}  // namespace atcoder
