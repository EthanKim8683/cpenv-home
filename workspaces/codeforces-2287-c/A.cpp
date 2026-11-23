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

const int MAXN = 5e4;
const int MAXM = 5e4;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vc<vi> divisors(MAXM + 1);
  vc<bool> is_sf(MAXM + 1, true);
  rep(i, 1, MAXM + 1) {
    if (i >= 2 and i * i <= MAXM) {
      is_sf[i * i] = false;
    }
    for (int j = i; j <= MAXM; j += i) {
      is_sf[j] = is_sf[j] and is_sf[i];
      if (is_sf[i]) {
        divisors[j].pb(i);
      }
    }
  }

  vc<bitset<MAXN + 1>> dp(MAXM + 1), dp2(MAXM + 1), dp3(MAXM + 1);
  dp2[0][0] = 1;
  rep(i, 1, MAXM + 1) {
    dp[i] ^= dp2[i - 1] << 1;
    for (auto e : divisors[i]) {
      if (e == 1) continue;
      dp[i] ^= dp3[e] << 1;
    }
    for (auto e : divisors[i]) {
      if (e == 1) continue;
      dp3[e] ^= dp[i];
    }
    dp2[i] = dp[i] ^ dp2[i - 1];
  }

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    cout << dp2[M][N] << '\n';
  }
}
