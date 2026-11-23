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
    int N;
    cin >> N;

    string A;
    cin >> A;

    vc dp(N + 1, vi(2 * N + 1, -1));
    dp[0][N] = -2;
    rep(i, 0, N) {
      rep(j, -i, i + 1) {
        if (dp[i][N + j] == -1) continue;
        int d = A[i] - '0';
        dp[i + 1][N + j + d] = j;
        dp[i + 1][N + j - d] = j;
      }
    }
    pii best = {N, N};
    rep(i, -N, N + 1) {
      if (dp[N][N + i] == -1) continue;
      chmin(best, pii{abs(i), i});
    }
    int j = best.sd;
    vi ans;
    for (int i = N; i >= 2; i--) {
      ans.pb(j - dp[i][N + j]);
      j = dp[i][N + j];
    }
    reverse(all(ans));
    for (auto e : ans) {
      cout << (e < 0 ? '-' : '+');
    }
    cout << '\n';
  }
}
