#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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
    int N;
    cin >> N;

    string S;
    cin >> S;

    vc dp(N + 1, vc(4 + 1, vi(4 + 1, 0)));
    rep(i, 0, N) {
      dp[i][0][0] += 1;
      rep(j, 0, 4 + 1) {
        rep(k, 0, 4 + 1) {
          int j2 = j, k2 = k;
          if (S[i] == '2' and (j == 0 or j == 2)) {
            j2++;
          }
          if (S[i] == '2' and (k == 0 or k == 2)) {
            k2++;
          }
          if (S[i] == '0' and j == 1) {
            j2++;
          }
          if (S[i] == '0' and k == 1) {
            k2++;
          }
          if (S[i] == '5' and j == 3) {
            j2++;
          }
          if (S[i] == '6' and k == 3) {
            k2++;
          }
          dp[i + 1][j2][k2] += dp[i][j][k];
        }
      }
    }

    vc dp2(N + 1, vc(4 + 1, vi(4 + 1, 0)));
    for (int i = N - 1; i >= 0; i--) {
      dp2[i + 1][4][4] += 1;
      rep(j, 0, 4 + 1) {
        rep(k, 0, 4 + 1) {
          int j2 = j, k2 = k;
          if (S[i] == '2' and (j == 1 or j == 3)) {
            j2--;
          }
          if (S[i] == '2' and (k == 1 or k == 3)) {
            k2--;
          }
          if (S[i] == '0' and j == 2) {
            j2--;
          }
          if (S[i] == '0' and k == 2) {
            k2--;
          }
          if (S[i] == '5' and j == 4) {
            j2--;
          }
          if (S[i] == '6' and k == 4) {
            k2--;
          }
          dp2[i][j2][k2] += dp2[i + 1][j][k];
        }
      }
      dp2[i + 1][4][4] -= 1;
    }

    rep(i, 0, N) {
      int ans = 0;
      rep(j, 0, 4 + 1) {
        rep(k, 0, 4 + 1) {
          rep(l, 0, 4 + 1) {
            rep(m, 0, 4 + 1) {
              if (j >= l and k < m) continue;
              ans += dp[i][j][k] * dp2[i][l][m];
            }
          }
        }
      }
      cout << ans << ' ';
    }
    cout << '\n';
  }
}
