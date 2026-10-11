template <class T>
T lucas_binom(long long n, long long k, int mod) {
  using T2 = double_width_t<T>;

  assert(mod > 0);
  if (n < 0 or k < 0) return 0;
  if (mod == 2) return (~n & k) == 0;

  assert(is_prime(mod));
  T rv = 1;
  while (n or k) {
    rv = (T2) rv * binom<T>(n % mod, k % mod) % mod;
    n /= mod;
    k /= mod;
  }
  return rv;
}
