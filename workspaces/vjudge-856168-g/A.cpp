#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

// #define int long long
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
const int MAXN = 2e5;
const int SQRTK = 710;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int dp[MAXN + 1][2];

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, K;
  cin >> N >> K;

  vi ans(N + 1, 0);
  dp[0][0] += 499122177;
  rep(j, 0, SQRTK) {
    rep(i, 0, N + 1) {
      if (i + K + j <= N) {
        (dp[i + K + j][j % 2] += dp[i][j % 2]) %= MOD;
        (dp[i + K + j][(j + 1) % 2] += dp[i][j % 2]) %= MOD;
      }
      if (i >= 1) {
        (ans[i] += dp[i][j % 2]) %= MOD;
      }
      dp[i][j % 2] = 0;
    }
  }
  rep(i, 1, N + 1) { cout << ans[i] << ' '; }
}
