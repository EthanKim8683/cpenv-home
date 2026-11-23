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

    vc<vi> adj(N + 1);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    auto solve = [&](int k) -> pii {
      vc<set<int>> sets(N + 1);
      int count1 = 0, count2 = 0;
      auto dfs = [&](auto self, int a, int p) -> void {
        bool black = false, gray = false;
        if (1 <= k - a and k - a <= N and k - a != a) {
          black = true;
          gray = true;
          sets[a].insert(a);
        }
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, a);
          if (sz(sets[b]) > 0) {
            gray = true;
          }
          if (sz(sets[b]) > sz(sets[a])) {
            swap(sets[a], sets[b]);
          }
          for (auto e : sets[b]) {
            if (sets[a].contains(k - e)) {
              sets[a].erase(k - e);
            } else {
              sets[a].insert(e);
            }
          }
          sets[b].clear();
        }
        if (black) {
          count1++;
        } else if (gray) {
          count2++;
        }
      };
      dfs(dfs, 1, -1);
      assert(sets[1].empty());
      return {count1, count2};
    };
    pair<pii, int> ans = {{0, 0}, 0};
    if (N % 2 == 1) {
      chmax(ans, pair{solve(N), N});
      chmax(ans, pair{solve(N + 1), N + 1});
      chmax(ans, pair{solve(N + 2), N + 2});
    } else {
      chmax(ans, pair{solve(N + 1), N + 1});
    }
    cout << ans.sd << '\n';
  }
}
