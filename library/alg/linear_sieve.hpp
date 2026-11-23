vi primes;
vc<bool> is_prime(MAXN + 1, true);
rep(i, 2, MAXN + 1) {
  if (is_prime[i]) {
    primes.pb(i);
  }
  for (auto e : primes) {
    if (i * e > MAXN) break;
    is_prime[i * e] = false;
    if (i % e == 0) {
      break;
    }
  }
}
