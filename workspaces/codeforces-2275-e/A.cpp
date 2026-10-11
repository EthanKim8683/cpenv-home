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
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    // vc dp(N, vc(2 + 1, vi(4, -INF)));
    // dp[0][1][0] = A[0] == B[0];
    // dp[0][0][2] = A[0] == B[0];
    // dp[0][2][3] = 0;
    // rep(i, 0, N - 1) {
    //   rep(j, 0, 2 + 1) {
    //     chmax(dp[i + 1][j][0],
    //           dp[i][j][0] + (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1][3], dp[i][j][0] + (B[i] == A[i + 1]));
    //     }

    //     chmax(dp[i + 1][j][1],
    //           dp[i][j][1] + (A[i] == B[i + 1]) + (B[i + 1] == A[i + 1]));
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1][2], dp[i][j][1] + (A[i] == B[i + 1]));
    //     }

    //     chmax(dp[i + 1][j][3],
    //           dp[i][j][2] + (B[i] == A[i + 1]) + (A[i] == B[i + 1]));
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1][0],
    //             dp[i][j][2] + (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
    //     }

    //     chmax(dp[i + 1][j][2],
    //           dp[i][j][3] + (A[i] == B[i + 1]) + (B[i] == A[i + 1]));
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1][1],
    //             dp[i][j][3] + (A[i] == B[i + 1]) + (B[i + 1] == A[i + 1]));
    //     }
    //   }
    // }
    // int ans = -INF;
    // chmax(ans, dp[N - 1][0][2]);
    // chmax(ans, dp[N - 1][0][3]);
    // chmax(ans, dp[N - 1][1][0]);
    // chmax(ans, dp[N - 1][1][1]);
    // chmax(ans, dp[N - 1][1][2] + (A[N - 1] == B[N - 1]));
    // chmax(ans, dp[N - 1][1][3] + (A[N - 1] == B[N - 1]));
    // chmax(ans, dp[N - 1][2][2] + (A[N - 1] == B[N - 1]));
    // chmax(ans, dp[N - 1][2][3] + (A[N - 1] == B[N - 1]));
    // ans += 2 * N - 1;
    // cout << ans << '\n';

    // vi ps1(N, 0), ps2(N, 0), ps3(N, 0), ps4(N + 1, 0);
    // rep(i, 0, N - 1) {
    //   ps1[i + 1] += (A[i] == B[i + 1]) + (B[i] == A[i + 1]);
    //   ps2[i + 1] += (A[i] == B[i + 1]);
    //   ps3[i + 1] += (B[i] == A[i + 1]);
    // }
    // rep(i, 0, N) { ps4[i + 1] += (A[i] == B[i]); }
    // rep(i, 0, N - 1) {
    //   ps1[i + 1] += ps1[i];
    //   ps2[i + 1] += ps2[i];
    //   ps3[i + 1] += ps3[i];
    // }
    // rep(i, 0, N) { ps4[i + 1] += ps4[i]; }

    if (N == 1) {
      cout << 1 + (A[0] == B[0]) << '\n';
      continue;
    }

    vi dp(4, -INF);
    // dp[0] = (A[0] == B[0]) + (A[0] == B[1]) + (B[0] == A[1]);
    dp[1] = (A[0] == B[1]) + (B[0] == A[1]) + (A[1] == B[1]);
    // dp[2] = (A[0] == B[0]) + (A[0] == B[1]) + (A[1] == B[1]);
    dp[3] = (A[0] == B[0]) + (B[0] == A[1]) + (A[1] == B[1]);
    rep(i, 1, N - 1) {
      vi dp2(4, -INF);
      chmax(dp2[0], dp[0] + (A[i] == B[i + 1]) + (B[i] == A[i + 1]));
      chmax(dp2[2], dp[0] + (A[i] == B[i + 1]) + (B[i + 1] == A[i + 1]));
      chmax(dp2[3], dp[0] + (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
      chmax(dp2[1], dp[1] - (A[i] == B[i]) + (A[i] == B[i + 1]) +
                        (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
      chmax(dp2[1], dp[2] - (A[i] == B[i]) + (A[i] == B[i + 1]) +
                        (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
      chmax(dp2[2], dp[2] + (A[i] == B[i + 1]) + (B[i + 1] == A[i + 1]));
      chmax(dp2[1], dp[3] - (A[i] == B[i]) + (A[i] == B[i + 1]) +
                        (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
      chmax(dp2[3], dp[3] + (B[i] == A[i + 1]) + (A[i + 1] == B[i + 1]));
      dp = dp2;
    }
    int ans = *max_element(all(dp));
    ans += 2 * N - 1;
    cout << ans << '\n';

    // vc dp(N + 1, vi(2 + 1, -INF));
    // dp[0][0] = A[0] == B[0];
    // rep(i, 0, N) {
    //   rep(j, 0, 2 + 1) {
    //     chmax(dp[i + 1][j], dp[i][j] - (A[i] == B[i]) + (A[i] == B[i + 1]) +
    //                             (B[i] == A[i + 1]) + (A[i + 1] + B[i + 1]));
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1], dp[i][j] - (A[i] == B[i]) +
    //                                   (A[i] == B[i + 1]) +
    //                                   (A[i + 1] + B[i + 1]));
    //     }
    //     if (j + 1 <= 2) {
    //       chmax(dp[i + 1][j + 1], dp[i][j] - (A[i] == B[i]) +
    //                                   (B[i] == A[i + 1]) +
    //                                   (A[i + 1] + B[i + 1]));
    //     }
    //   }
    // }
  }
}
