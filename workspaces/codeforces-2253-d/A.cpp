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

const int MAXK = 2e4;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  // bitset<100 * (100 + 1) / 2 + 1> dp;
  // dp[0] = 1;
  // rep(i, 1, 100 + 1) {
  //   dp |= dp << i;
  //   bool ok = true;
  //   rep(j, 0, i * (i + 1) / 2 + 1) { ok = ok and dp[j]; }
  //   if (!ok) cerr << i << ' ';
  // }
  // cerr << '\n';

  int T;
  cin >> T;

  while (T--) {
    int X, Y;
    cin >> X >> Y;

    auto solve = [&](int k) -> pii {
      int z = Y - k * (k + 1) / 2, p = (X - z) / 2;
      chmax(p, 0);
      chmin(p, k * (k + 1) / 2);
      chmin(p, X);
      chmax(p, k * (k + 1) / 2 - Y);
      int q = k * (k + 1) / 2 - p;
      return {p, q};
    };
    pii best = {INF, -1};
    rep(k, 1, MAXK + 1) {
      auto [p, q] = solve(k);
      if (!(0 <= p and p <= X and 0 <= q and q <= Y)) continue;
      chmin(best, pair{(p - X) * (p - X) + (q - Y) * (q - Y), k});
    }

    int k = best.sd;
    auto [p, q] = solve(k);
    string ans(k, 'Y');
    for (int i = k; i >= 1; i--) {
      if (p - i >= 0) {
        ans[k - i] = 'X';
        p -= i;
      }
    }
    cout << ans << '\n';
  }
}
