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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<vi> adj(N);
    rep(i, 0, M) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vc<bool> seen(N, false);
    vi ans(N);
    auto dfs = [&](auto self, int a, int d) -> void {
      if (seen[a]) return;
      seen[a] = true;
      ans[a] = d;
      for (auto b : adj[a]) {
        self(self, b, d + 1);
      }
    };
    dfs(dfs, 0, 0);
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
