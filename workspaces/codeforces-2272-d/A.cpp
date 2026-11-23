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
    int K;
    cin >> K;

    vc<vc<vi>> trees(K);
    for (auto &adj : trees) {
      int N;
      cin >> N;

      adj.resize(N);
      rep(i, 0, N - 1) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
      }
    }

    int t0 = -1;
    rep(i, 0, K) {
      if (sz(trees[i]) > 1) {
        t0 = i;
      }
    }
    if (t0 == -1) {
      rep(i, 1, K) { cout << "1 1 " << i + 1 << " 1\n"; }
      continue;
    }

    auto solve = [&](vc<vi> &adj) -> int {
      int N = sz(adj);

      vc dp(N, vi(2, -INF));
      auto dfs = [&](auto self, int a, int p) -> void {
        dp[a] = {0, 1};
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, a);
          vi dp2(2, -INF);
          rep(i, 0, 2) {
            rep(j, 0, 2) {
              if (i & j) continue;
              chmax(dp2[i], dp[a][i] + dp[b][j]);
            }
          }
          dp[a] = dp2;
        }
      };
      dfs(dfs, 0, -1);

      if (dp[0][1] > dp[0][0]) {
        if (sz(adj[0]) >= 1) {
          return adj[0][0];
        } else {
          return 0;
        }
      } else {
        return 0;
      }
    };
    int u0 = solve(trees[t0]);
    rep(i, 0, K) {
      if (i == t0) continue;
      cout << t0 + 1 << ' ' << u0 + 1 << ' ' << i + 1 << ' '
           << solve(trees[i]) + 1 << '\n';
    }
  }
}
