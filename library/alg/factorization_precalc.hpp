// https://en.algorithmica.org/hpc/algorithms/factorization/#lookup-table
// https://en.algorithmica.org/hpc/algorithms/factorization/#precomputed-primes
// Factorization table and magic primes
/* constexpr */ struct __factorization_precalc {
  unsigned short sieve[1 << 16];
  unsigned long long magic_primes[6542];

  constexpr __factorization_precalc() : sieve(0) {
    int k = 0;
    for (unsigned int i = 2; i < (1 << 16); i++) {
      if (sieve[i] != 0) continue;
      sieve[i] = i;
      magic_primes[k] = (unsigned long long) -1 / i + 1;
      k++;
      for (unsigned int j = i * i; j < (1 << 16); j += i) {
        if (sieve[j] != 0) continue;
        sieve[j] = i;
      }
    }
  }
} fp;
