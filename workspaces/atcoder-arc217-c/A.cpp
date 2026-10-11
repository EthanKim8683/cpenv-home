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
const int MAXN = 100;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int T;
  cin >> T;

  while (T--) {
    int N, C;
    cin >> N >> C;

    vi A(N);
    for (auto &e : A) cin >> e;

    sort(all(A));
    reverse(all(A));

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

    auto binom = [&](int n, int k) -> int {
      return fact[n] * mod_inv(fact[n - k] * fact[k]) % MOD;
    };

    int ub = C + 1;
    // index
    // num customers
    // max(ps, 0)
    vc dp(N + 1, vc(N + 1, vi(N + 1, 0)));
    dp[0][0][0] = 1;
    rep(i, 0, N) {
      int lb = A[i];
      rep(j, 0, N + 1) {
        rep(l, 0, N + 1 - j) {
          int w = mod_pow(ub - lb, l) * binom(N - j, l) % MOD;
          rep(k, 0, j + 1) {
            (dp[i + 1][j + l][max(k + l - 1, 0ll)] += dp[i][j][k] * w) %= MOD;
          }
        }
      }
      ub = lb;
    }
    vi ans(N + 1, 0);
    rep(i, 0, N + 1) {
      rep(j, 0, i + 1) {
        (ans[i - j] += dp[N][i][j] * mod_pow(ub - 1, N - i)) %= MOD;
      }
    }
    int w = mod_inv(mod_pow(C, N));
    for (auto e : ans) {
      cout << e * w % MOD << ' ';
    }
    cout << '\n';
  }
}
