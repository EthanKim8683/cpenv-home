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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int X, Y, M;
    cin >> X >> Y >> M;

    string S;
    cin >> S;

    vc dp(M + 1, vc(X + M + 1, vc<bool>(Y + M + 1, false)));
    dp[0][X][Y] = true;
    int ans = 0;
    pii best = {X + Y, 0};
    rep(i, 0, M + 1) {
      rep(j, max(X - i, 0ll), X + i + 1) {
        rep(k, max(Y - i, 0ll), Y + i + 1) {
          if (!dp[i][j][k]) continue;
          chmax(ans, j + k);
          chmax(best, pii{j + k, -i});
          if (i < M) {
            if (S[i] == '+') {
              if (j - 1 >= 0) {
                dp[i + 1][j - 1][k + 1] = true;
              }
              if (k > 0) {
                dp[i + 1][j][k + 1] = true;
              }
            } else {
              if (j - 1 >= 0) {
                dp[i + 1][j - 1][k] = true;
              }
              if (k - 1 >= 0) {
                dp[i + 1][j + 1][k - 1] = true;
              }
            }
          }
        }
      }
    }
    // cout << ans << '\n';
    cerr << -best.sd << ' ' << X + Y + (-best.sd + 1) / 3 << ' ' << X + 2 * Y
         << '\n';
  }
}
