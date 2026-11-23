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

const int LOGN = 18;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // you basically don't want to encounter another guy with >=x+d
  //
  // maybe for each subtree, you see who's the weakest guy that can win
  //
  // can we use this to join subtrees? yeeeeess?
  //
  // now to solve for each player, i imagine you can binary lift on the tree to
  // see which subtree where the weakest is still stronger
  //
  // ah i'm dumb its small to large

  int T;
  cin >> T;

  while (T--) {
    int N, D;
    cin >> N >> D;

    vc<vi> adj(2 * N - 1);
    rep(i, N, 2 * N - 1) {
      int p1, p2;
      cin >> p1 >> p2;
      p1--, p2--;
      adj[i].pb(p1);
      adj[i].pb(p2);
    }

    // vc anc(2 * N, vi(LOGN + 2));
    // vi dp(2 * N);
    // auto dfs = [&](auto self, int a, int p) -> void {
    //   anc[a][0] = p;
    //   if (sz(adj[a]) == 0) {
    //     dp[a] = -a;
    //   } else {
    //     int b1 = adj[a][0], b2 = adj[a][1];
    //     self(self, b1, a);
    //     self(self, b2, a);
    //     dp[a] = INF;
    //     if (dp[b1] + D > dp[b2]) {
    //       chmin(dp[a], dp[b1]);
    //     }
    //     if (dp[b2] + D > dp[b1]) {
    //       chmin(dp[a], dp[b2]);
    //     }
    //   }
    // };
    // dfs(dfs, 2 * N - 2, 2 * N - 1);
    // anc[2 * N - 1][0] = 2 * N - 1;
    // dp[2 * N - 1] = INF;
    // rep(i, 1, LOGN + 2) {
    //   rep(j, 0, 2 * N) { anc[j][i] = anc[anc[j][i - 1]][i - 1]; }
    // }
    // for (auto e : dp) {
    //   cerr << e << ' ';
    // }
    // cerr << '\n';
    // rep(i, 0, N) {
    //   int a = i, ans = 0;
    //   for (int j = LOGN + 1; j >= 0; j--) {
    //     if (dp[anc[a][j]] <= -i) {
    //       a = anc[a][j];
    //       ans += 1ll << j;
    //     }
    //   }
    //   cout << ans << ' ';
    // }
    // cout << '\n';

    vc<map<int, int, greater<>>> dp(2 * N - 1);
    vi ans(N);
    auto dfs = [&](auto self, int a, int d) -> void {
      if (sz(adj[a]) == 0) {
        dp[a].emplace(a, d);
      } else {
        int b1 = adj[a][0], b2 = adj[a][1];
        self(self, b1, d + 1);
        self(self, b2, d + 1);
        int w1 = dp[b1].begin()->fs, w2 = dp[b2].begin()->fs;
        while (sz(dp[b1]) > 0) {
          auto [c, d2] = *dp[b1].begin();
          if (c - D < w2) break;
          ans[c] = d2 - d;
          dp[b1].erase(dp[b1].begin());
        }
        while (sz(dp[b2]) > 0) {
          auto [c, d2] = *dp[b2].begin();
          if (c - D < w1) break;
          ans[c] = d2 - d;
          dp[b2].erase(dp[b2].begin());
        }
        if (sz(dp[b1]) > sz(dp[b2])) {
          dp[a].swap(dp[b1]);
          for (auto e : dp[b2]) {
            dp[a].insert(e);
          }
        } else {
          dp[a].swap(dp[b2]);
          for (auto e : dp[b1]) {
            dp[a].insert(e);
          }
        }
      }
    };
    dfs(dfs, 2 * N - 2, 0);
    for (auto [a, d] : dp[2 * N - 2]) {
      ans[a] = d;
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
