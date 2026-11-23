auto binom = [&](int n, int k) -> int {
  if (n < 0 or n - k < 0 or k < 0) return 0;
  return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
};
