#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
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

  int N, K;
  cin >> N >> K;

  vi A(3 + 1, 0);
  rep(i, 0, K + 1) { cin >> A[i]; }

  int sum = -1 * A[0] + 1 * A[2] + 2 * A[3];
  if (sum < -1) {
    cout << "0\n";
    exit(0);
  }
  if (sum == -1) {
    A[0] -= 1;
  }

  vc dp(2, vc(A[2] + 1, vc<double>(A[3] + 1, 0)));
  dp[0][0][0] = 1;
  rep(i, 0, A[0] + 1) {
    rep(j, 0, A[2] + 1) {
      rep(k, 0, A[3] + 1) {
        if (i * -1 + j * 1 + k * 2 < 0) {
          dp[i % 2][j][k] = 0;
        }
        int n1 = A[0] - i, n2 = A[2] - j, n3 = A[3] - k, d = n1 + n2 + n3;
        if (i + 1 <= A[0]) {
          dp[(i + 1) % 2][j][k] += dp[i % 2][j][k] * n1 / d;
        }
        if (j + 1 <= A[2]) {
          dp[i % 2][j + 1][k] += dp[i % 2][j][k] * n2 / d;
        }
        if (k + 1 <= A[3]) {
          dp[i % 2][j][k + 1] += dp[i % 2][j][k] * n3 / d;
        }
        if (i == A[0] and j == A[2] and k == A[3]) {
          double ans = dp[i % 2][j][k];
          if (sum == -1) {
            ans *= (double) (A[0] + 1) / N;
          }
          cout << setprecision(10) << fixed << ans << '\n';
        }
        dp[i % 2][j][k] = 0;
      }
    }
  }
}
