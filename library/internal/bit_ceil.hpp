namespace atcoder {
namespace internal {

#if __cplusplus >= 202002L

using std::bit_ceil;

#else

// @return same with std::bit::bit_ceil
unsigned int bit_ceil(unsigned int n) {
  unsigned int x = 1;
  while (x < (unsigned int) (n)) x *= 2;
  return x;
}

#endif

}  // namespace internal
}  // namespace atcoder
