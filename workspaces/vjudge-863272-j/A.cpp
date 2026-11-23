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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // dp store for each subtree min cost to make size at most i
  //
  // how to convolute?
  //
  // we can binary search to get rid of max size dimension
  //
  // larger is cheaper... can we say that it's convex? i don't think so
  //
  // maybe let's think of it in terms of ranges
  //
  // yes
  //
  // no

  int N, T;
  cin >> N >> T;

  vc<vc<pii>> adj(N);
  rep(i, 0, N - 1) {
    int u, v, t;
    cin >> u >> v >> t;
    u--, v--;
    adj[u].eb(v, t);
    adj[v].eb(u, t);
  }

  vc<vc<pii>> adj2(N);
  vi size(N), order;
  auto dfs = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto [b, w] : adj[a]) {
      if (b == p) continue;
      size[a] += self(self, b, a);
      adj2[a].eb(b, w);
    }
    order.pb(a);
    return size[a];
  };
  dfs(dfs, 0, -1);

  auto check = [&](int x) -> bool {
    vc<vi> dp(N);
    for (auto e : order) {
      if (sz(adj2[e]) == 0) {
        dp[e] = {INF, 0};
        continue;
      }

      auto dfs2 = [&](auto self, int l, int r) -> vi {
        if (r - l == 1) {
          auto [b, w] = adj2[e][l];
          vi rv = dp[b];
          for (auto e : rv) {
            chmin(rv[0], e + w);
          }
          return rv;
        }

        int sum = 0, m = l;
        while (m + 1 < r and 2 * sum < size[e]) {
          sum += size[adj2[e][m].fs];
          m++;
        }

        auto dp1 = self(self, l, m), dp2 = self(self, m, r);
        vi rv(min(sz(dp1) + sz(dp2) - 1, x + 1), INF);
        rep(i, 0, sz(dp1)) {
          rep(j, 0, min(sz(dp2), sz(rv) - i)) {
            chmin(rv[i + j], dp1[i] + dp2[j]);
          }
        }
        return rv;
      };
      dp[e] = dfs2(dfs2, 0, sz(adj2[e]));
      dp[e].insert(dp[e].begin(), INF);
      if (sz(dp[e]) > x + 1) {
        dp[e].pop_back();
      }
    }
    return *min_element(all(dp[order.back()])) <= T;
  };
  int l = 1, r = N;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  cout << l << '\n';
}
