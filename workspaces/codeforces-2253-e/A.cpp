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

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi par(N);
    pii furthest = {0, -1};
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      par[a] = p;
      chmax(furthest, pii{d, a});
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
    };
    dfs(dfs, 0, -1, 0);
    int e1 = furthest.sd;
    furthest = {0, -1};
    dfs(dfs, e1, -1, 0);
    int e2 = furthest.sd;
    vi path;
    for (int a = e2; a != e1; a = par[a]) {
      path.pb(a);
    }
    path.pb(e1);
    assert(sz(path) % 2 == 0);

    vc<set<int>> halves(N);
    auto dfs2 = [&](auto self, int a, int p, int d) -> bool {
      int count = 0;
      if (d == (sz(path) - 1) / 2) {
        count++;
        halves[a].insert(d);
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        if (self(self, b, a, d + 1)) {
          count++;
        }
        if (sz(halves[b]) > sz(halves[a])) {
          swap(halves[a], halves[b]);
        }
        for (auto e : halves[b]) {
          halves[a].insert(e);
        }
        halves[b].clear();
      }
      if (count >= 2) {
        halves[a].insert(d);
      }
      return count >= 1;
    };
    set<int> ans;
    int r1 = path[sz(path) / 2 - 1], r2 = path[sz(path) / 2];
    dfs2(dfs2, r1, r2, 0);
    dfs2(dfs2, r2, r1, 0);
    for (auto e1 : halves[r1]) {
      for (auto e2 : halves[r2]) {
        ans.insert(e1 + 1 + e2);
      }
    }
    cout << sz(ans);
    for (auto e : ans) {
      cout << ' ' << e;
    }
    cout << '\n';
  }
}
