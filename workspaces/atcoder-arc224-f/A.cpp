#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

const int LOGA = 60;
const int MAXN = 2e5;
const int MOD = 998244353;

int mod_pow(int a, int b, int m = MOD) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}

int mod_inv(int a, int m = MOD) { return mod_pow(a, m - 2); }

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) fact[i] = fact[i - 1] * i % MOD;

  vi inv_fact(MAXN + 1);
  rep(i, 0, MAXN + 1) inv_fact[i] = mod_inv(fact[i]);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto binom = [&](int n, int k) -> int {
      if (n < 0 or n - k < 0 or k < 0) return 0;
      return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
    };

    auto binom_le = [&](int n, int k) -> int {
      int rv = 0;
      rep(i, 0, k + 1) { (rv += binom(n, i)) %= MOD; }
      return rv;
    };

    auto check = [&](int x) -> bool {
      int worst = 0;
      for (int i = N - 1; i >= 0; i--) {
        if ((A[i] & x) != 0) {
          x &= ~A[i];
          chmax(worst, N - i);
        }
      }
      return x == 0 and worst <= K;
    };
    int m = 0;
    for (int i = LOGA - 1; i >= 0; i--) {
      if (check(m | 1ll << i)) {
        m |= 1ll << i;
      }
    }
    if (m == 0) {
      cout << binom_le(N, K) << '\n';
      continue;
    }

    int i = N - 1, k = K - 1, sum = binom_le(i, k), ans = 0;
    while (true) {
      for (; i >= 0; i--) {
        if ((A[i] & m) != 0) {
          if ((m & ~A[i]) == 0) break;
          m &= ~A[i];
        }
        // binom(n, k) = binom(n - 1, k - 1) + binom(n - 1, k)
        // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K (binom(N - 1, k - 1) +
        //   binom(N - 1, k))
        // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K binom(N - 1, k - 1) +
        //   \sum_{k=0}^K binom(N - 1, k)
        // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K binom(N - 1, k - 1) +
        //   \sum_{k=1}^{K+1} binom(N - 1, k - 1)
        // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K binom(N - 1, k - 1) +
        //   \sum_{k=0}^K binom(N - 1, k - 1) - binom(N - 1, 0 - 1) + binom(N -
        //   1, (K + 1) - 1)
        // \sum_{k=0}^K binom(N, k) = 2\sum_{k=0}^K binom(N - 1, k - 1) -
        //   binom(N - 1, 0 - 1) + binom(N - 1, (K + 1) - 1)
        // 2\sum_{k=0}^K binom(N - 1, k - 1) = \sum_{k=0}^K binom(N, k) +
        //   binom(N - 1, 0 - 1) + binom(N - 1, (K + 1) - 1)
        // \sum_{k=0}^K binom(N - 1, k - 1) = (\sum_{k=0}^K binom(N, k) +
        //   binom(N - 1, 0 - 1) + binom(N - 1, (K + 1) - 1)) / 2
        sum = (sum + binom(i - 1, 0 - 1) + MOD - binom(i - 1, (k + 1) - 1)) %
              MOD * mod_inv(2) % MOD;
        k--;
      }
      if (i < 0) break;
      (ans += sum) %= MOD;
      // binom(n, k) = binom(n - 1, k - 1) + binom(n - 1, k)
      // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K (binom(N - 1, k - 1) +
      //   binom(N - 1, k))
      // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K binom(N - 1, k - 1) +
      //   \sum_{k=0}^K binom(N - 1, k)
      // \sum_{k=0}^K binom(N, k) = \sum_{k=-1}^{K-1} binom(N - 1, k) +
      //   \sum_{k=0}^K binom(N - 1, k)
      // \sum_{k=0}^K binom(N, k) = \sum_{k=0}^K binom(N - 1, k) + binom(N - 1,
      //   -1) - binom(N - 1, K) + \sum_{k=0}^K binom(N - 1, k)
      // \sum_{k=0}^K binom(N, k) = 2\sum_{k=0}^K binom(N - 1, k) + binom(N - 1,
      //   -1) - binom(N - 1, K)
      // 2\sum_{k=0}^K binom(N - 1, k) = \sum_{k=0}^K binom(N, k) - binom(N - 1,
      //   -1) + binom(N - 1, K)
      // \sum_{k=0}^K binom(N - 1, k) = (\sum_{k=0}^K binom(N, k) - binom(N - 1,
      //   -1) + binom(N - 1, K)) / 2
      sum = (sum + MOD - binom(i - 1, -1) + binom(i - 1, k)) % MOD *
            mod_inv(2) % MOD;
      i--;
    }
    cout << ans << '\n';
  }
}
