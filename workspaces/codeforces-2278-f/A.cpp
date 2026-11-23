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

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc dp(N + 1, vi(M + 2 + 1, 0));
    rep(i, 0, N) {
      (dp[i + 1][2] += 1) %= MOD;
      (dp[i + 1][2 + 1] += MOD - 1) %= MOD;
      rep(j, 0, M + 2 + 1) {
        (dp[i + 1][j] += dp[i][j]) %= MOD;
        if (2 * j <= M + 2) {
          (dp[i + 1][2 * j] += MOD - dp[i][j]) %= MOD;
        }
        if (j + 1 <= M + 2) {
          (dp[i + 1][j + 1] += dp[i + 1][j]) %= MOD;
        }
      }
    }
    cout << dp[N][M + 2] << '\n';
  }
}
