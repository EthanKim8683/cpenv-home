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

const int MAXN = 100;
const int MAXX = 600;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  auto check = [&](string X) -> int {
    // string X;
    // cin >> X;

    int N = sz(X);

    vc<pii> ranges;
    for (int i = 0, j; i < N; i = j) {
      for (j = i + 1; j < N; j++) {
        if (X[j] == X[j - 1]) break;
      }
      ranges.eb(i, j);
    }

    int ans = 0;
    for (auto [l, r] : ranges) {
      vi indices1, indices2;
      int t = 0;
      rep(i, l, r) {
        if (X[i] == 'C') {
          indices2.pb(t);
        }
        if (X[i] != 'R') {
          indices1.pb(t);
          t++;
        }
      }
      rep(i, 0, sz(indices2)) { ans += indices2[i] - indices1[i]; }
    }
    return ans;
  };

  int X;
  cin >> X;

  auto solve = [&](int X) -> string {
    vc dp(X + 1, vc<pii>(MAXN / 2 + 1, {INF, INF}));
    dp[0][0] = {0, 0};
    for (int i = MAXN / 2 - 1; i >= 0; i--) {
      for (int j = X; j >= 0; j--) {
        rep(k, 0, MAXN / 2 + 1) {
          auto [n, p] = dp[j][k];
          if (j < j + i - k and j + i - k <= X and k + 1 <= MAXN / 2) {
            chmin(dp[j + i - k][k + 1], pii{n + 1, i});
          }
        }
      }
    }

    int i = X, j = 0;
    for (; j < MAXN / 2 + 1; j++) {
      auto [n, p] = dp[i][j];
      if (n != INF) break;
    }

    vc<bool> seen(MAXN / 2, false);
    while (i != 0) {
      auto [n, p] = dp[i][j];
      seen[p] = true;
      j--;
      i -= p - j;
    }

    string ans = "";
    rep(i, 0, MAXN / 2) {
      ans += seen[i] ? 'C' : 'A';
      ans += 'R';
    }
    return ans;
  };

  // rep(i, 0, MAXX + 1) {
  //   if (check(solve(i)) != i) {
  //     cerr << i << ' ' << check(solve(i)) << ' ' << solve(i) << '\n';
  //   }
  // }
  // cerr << '\n';

  cout << solve(X) << '\n';
}
