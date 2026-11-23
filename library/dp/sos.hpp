rep(i, 0, N) rep(j, 0, 1 << N) if (~i >> j & 1) dp[i | 1 << j] += dp[i];
