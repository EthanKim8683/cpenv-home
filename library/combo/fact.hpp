vi fact(MAXN + 1);
fact[0] = 1;
rep(i, 1, MAXN + 1) fact[i] = fact[i - 1] * i % MOD;
