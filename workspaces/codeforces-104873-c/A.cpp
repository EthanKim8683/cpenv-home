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
const int MAXN = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  vi ans(MAXN + 1, 0), dp(MAXN + 1, 0);
  dp[0] = 1;
  for (int i = 1; i * i <= MAXN; i++) {
    for (int j = 0; j + i <= MAXN; j++) {
      (dp[j + i] += dp[j]) %= MOD;
    }
    for (int j = 0; i * i + 2 * j <= MAXN; j++) {
      (ans[i * i + 2 * j] += dp[j]) %= MOD;
    }
  }

  while (T--) {
    int N;
    cin >> N;

    cout << ans[N] << '\n';
  }
}
