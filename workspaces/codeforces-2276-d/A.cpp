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

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<vi> adj(N);
    rep(i, 0, M) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].pb(b);
      adj[b].pb(a);
    }

    bool found = false;
    for (auto e : adj) {
      found = found or sz(e) == 0;
    }
    if (found) {
      cout << "Brain Melt\n";
      continue;
    }

    found = false;
    vc<bool> seen(N, false);
    int n = 0;
    auto dfs2 = [&](auto self, int a, int p) -> void {
      if (seen[a]) {
        found = true;
        return;
      }
      seen[a] = true;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    rep(i, 0, N) {
      if (seen[i]) continue;
      dfs2(dfs2, i, -1);
      n++;
    }
    if (found) {
      cout << "Many\n";
      continue;
    }
    if (n > 1) {
      cout << "Many\n";
      continue;
    }

    vi seen2(N, 0);
    pii furthest;
    auto dfs = [&](auto self, int a, int d, int k) -> void {
      if (seen2[a] >= k) return;
      seen2[a] = k;
      chmax(furthest, pii{d, a});
      for (auto b : adj[a]) {
        self(self, b, d + 1, k);
      }
    };
    int diameter = 0;
    rep(i, 0, N) {
      if (seen2[i] != 0) continue;
      furthest = {0, -1};
      dfs(dfs, i, 0, 1);
      dfs(dfs, furthest.sd, 0, 2);
      chmax(diameter, furthest.fs);
    }
    if (diameter > 2) {
      cout << "Many\n";
      continue;
    }

    cout << "2\n";
  }
}
