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
    int R, C;
    cin >> R >> C;

    vc A(R, vi(C));
    for (auto &r : A) {
      for (auto &e : r) {
        cin >> e;
      }
    }

    vi D(C);
    for (auto &e : D) cin >> e;

    if (C < R) {
      int ans = INF;
      rep(i, 0, 1 << C) {
        if (i == 0) continue;
        vi prices(R, INF);
        int cost = 0;
        rep(j, 0, C) {
          if (~i >> j & 1) continue;
          cost += D[j];
          rep(k, 0, R) { chmin(prices[k], A[k][j]); }
        }
        cost += accumulate(all(prices), 0ll);
        chmin(ans, cost);
      }
      cout << ans << '\n';
    } else {
      vi dp(1 << R, INF);
      dp[0] = 0;
      rep(i, 0, C) {
        vi dp2 = dp;
        for (auto &e : dp2) {
          e += D[i];
        }
        rep(j, 0, 1 << R) {
          chmin(dp[j], dp2[j]);
          rep(k, 0, R) {
            if (j >> k & 1) continue;
            chmin(dp2[j | 1 << k], dp2[j] + A[k][i]);
          }
        }
      }
      cout << dp[(1 << R) - 1] << '\n';
    }
  }
}
