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

const int LOGK = 4;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    sort(all(A));

    if (N == K) {
      cout << A[N - 1] << '\n';
      continue;
    }

    vc dp(LOGK + 1, vi(1 << (N - 1), -INF));
    rep(i, 0, 1 << (N - 1)) {
      dp[0][i] = 0;
      rep(j, 0, N - 1) {
        if (~i >> j & 1) continue;
        dp[0][i] += A[j];
      }
    }
    rep(k, 1, LOGK + 1) {
      rep(i, 0, 1 << (N - 1)) {
        for (int j = 0; j < i; j = ((j | ~i) + 1) & i) {
          chmax(dp[k][i], min(dp[k - 1][j], dp[k - 1][j ^ i]));
        }
      }
    }

    vc dp2(2, vi(1 << (N - 1), -INF));
    int t = 0;
    rep(i, 0, 1 << (N - 1)) { dp2[t][i] = INF; }
    rep(k, 0, LOGK + 1) {
      if (~K >> k & 1) continue;
      t ^= 1;
      for (int i = (1 << (N - 1)) - 1; i >= 0; i--) {
        for (int j = 0; j < i; j = ((j | ~i) + 1) & i) {
          chmax(dp2[t][i], min(dp2[t ^ 1][j], dp[k][j ^ i]));
        }
        dp2[t ^ 1][i] = -INF;
      }
    }
    cout << dp2[t][(1 << (N - 1)) - 1] + A[N - 1] << '\n';
  }
}
