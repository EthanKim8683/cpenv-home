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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    string S;
    cin >> S;

    int ans = INF;
    rep(i, 0, N + 1) {
      vc dp(N + 1, vi(N + 1, INF));
      dp[0][0] = 0;
      rep(j, 0, N) {
        rep(k, 0, j + 1) {
          if (k >= K) {
            chmin(dp[j + 1][k], dp[j][k] + (S[j] != 'L'));
          }
          if (i - (j - k) >= K) {
            chmin(dp[j + 1][k + 1], dp[j][k] + (S[j] != 'R'));
          }
        }
      }
      chmin(ans, dp[N][N - i]);
    }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
