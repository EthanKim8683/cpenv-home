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
    int N, M;
    cin >> N >> M;

    vc<set<int>> adj(N);
    rep(i, 0, N - 1) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      adj[x].insert(y);
      adj[y].insert(x);
    }

    vi V(M);
    for (auto &e : V) {
      cin >> e;
      e--;
    }

    vi dist(N);
    auto dfs2 = [&](auto self, int a, int p, int d) -> void {
      dist[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
    };
    dfs2(dfs2, N - 1, -1, 0);
    int ans = dist[0];

    vc<char> has_V(N, false);
    for (auto e : V) {
      has_V[e] = true;
    }
    auto dfs = [&](auto self, int a, int p) -> bool {
      for (auto b : adj[a]) {
        if (b == p) continue;
        has_V[a] |= self(self, b, a);
      }
      return has_V[a];
    };
    for (auto it = adj[0].begin(); it != adj[0].end();) {
      int b = *it;
      if (dfs(dfs, b, 0)) {
        it = adj[0].erase(it);
        adj[b].erase(0);
      } else {
        it++;
      }
    }

    fill(all(dist), -INF);
    dfs2(dfs2, N - 1, -1, 0);
    for (auto e : V) {
      chmax(ans, dist[e] + 1);
    }
    cout << ans << '\n';
  }
}
