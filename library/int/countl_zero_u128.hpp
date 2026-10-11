constexpr int countl_zero(unsigned __int128 n) {
  if (n == 0) return 0;

  int ans = 0;
  if (n >> 64) {
    return __builtin_clzll(n >> 64);
  } else {
    return 64 + __builtin_clzll(n);
  }
  return ans;
}
