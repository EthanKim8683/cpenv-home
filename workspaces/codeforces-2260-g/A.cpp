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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vi primes, mu(N + 1);
  vc<bool> is_prime(N + 1, true);
  mu[1] = 1;
  for (int i = 2; i <= N; i++) {
    if (is_prime[i]) {
      mu[i] = -1;
      primes.pb(i);
    }
    for (auto e : primes) {
      if (i * e > N) break;
      is_prime[i * e] = false;
      if (i % e == 0) {
        mu[i * e] = 0;
      } else {
        mu[i * e] = mu[i] * mu[e];
      }
    }
  }

  vi fact(N + 1);
  fact[0] = 1;
  rep(i, 1, N + 1) { fact[i] = fact[i - 1] * i % MOD; }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  vi inv_fact(N + 1);
  rep(i, 0, N + 1) { inv_fact[i] = mod_inv(fact[i]); }

  auto binom = [&](int n, int k) -> int {
    return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
  };

  int ans = 1;
  for (int i = 2; i <= N; i++) {
    int k = N / i;
    (ans += -mu[i] * binom(N, k) % MOD * fact[k]) %= MOD;
  }
  (ans += MOD) %= MOD;
  cout << ans << '\n';
}
