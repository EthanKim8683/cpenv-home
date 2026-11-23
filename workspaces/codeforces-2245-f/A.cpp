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

const int MAXN = 500;
const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // count = # of popped
  //
  // why is this not easy
  //
  // it's not easy because the number to insert is not squeezed
  //
  // cartesian tree?
  //
  // pop all remaining on left. so to get A[i], it's like dp[i][A[i]]
  //
  // we can combine left and right using binom?

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
      if (y & 1) (rv *= x) %= MOD;
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) fact[i] = fact[i - 1] * i % MOD;

  vi inv_fact(MAXN + 1);
  rep(i, 0, MAXN + 1) inv_fact[i] = mod_inv(fact[i]);

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or n - k < 0 or k < 0) return 0;
    return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
  };

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc dp(N + 1, vc(N + 1, vi(N + 1, -1)));
    auto dfs = [&](auto self, int l, int r, int d) -> int {
      if (d < 0) return 0;
      if (r - l == 0) {
        if (d != 0) return 0;
        return 1;
      }
      if (dp[l][r][d] != -1) return dp[l][r][d];
      int sum = 0;
      rep(i, l, r) {
        if (A[i] == -1) {
          rep(j, 0, i - l + 1) {
            (sum += self(self, l, i, j) * self(self, i + 1, r, d - 1) % MOD *
                    binom(r - l - 1, i - l)) %= MOD;
          }
        } else {
          (sum += self(self, l, i, A[i]) * self(self, i + 1, r, d - 1) *
                  binom(r - l - 1, i - l)) %= MOD;
        }
      }
      return dp[l][r][d] = sum;
    };
    int ans = 0;
    rep(i, 0, N + 1) { (ans += dfs(dfs, 0, N, i)) %= MOD; }
    cout << ans << '\n';
  }
}
