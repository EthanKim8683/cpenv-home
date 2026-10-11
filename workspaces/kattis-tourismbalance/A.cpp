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

  int N, K;
  cin >> N >> K;

  vi V(N);
  for (auto &e : V) cin >> e;

  vc<vi> adj(N);
  rep(i, 0, N) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }

  vi seen(N, 0);
  vi color(N, 1);
  auto dfs = [&](auto self, int a, int p) -> int {
    if (seen[a] == 2) return -1;
    if (seen[a] == 1) return a;

    seen[a] = 1;
    int rv = -1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      int c = self(self, b, a);
      if (c != -1) {
        rv = c;
      }
    }
    seen[a] = 2;

    if (rv != -1) {
      color[a] = 2;
    }
    if (rv == a) {
      rv = -1;
    }
    return rv;
  };
  dfs(dfs, 0, -1);
  // if (find(all(color), 2) == color.end()) {
  //   fill(all(color), 2);
  // }

  vi groups(N);
  auto dfs2 = [&](auto self, int a, int p, int g) -> void {
    groups[a] = g;
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (color[b] != 1) continue;
      self(self, b, a, g);
    }
  };
  rep(i, 0, N) {
    if (color[i] != 2) continue;
    dfs2(dfs2, i, -1, i);
  }
  // for (auto e : color) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';

  int ans = 0;
  map<int, int> counts1;
  map<pii, int> counts2;
  rep(i, 0, N) {
    int g = groups[i];

    int same = counts2[pii{g, V[i] - K}];
    if (K != 0) {
      same += counts2[pii{g, V[i] + K}];
    }

    int diff = counts1[V[i] - K];
    if (K != 0) {
      diff += counts1[V[i] + K];
    }
    diff -= same;

    if (K == 0) {
      ans += 1;
    }

    int contrib = 1 * same + 2 * diff;
    if (K == 0) {
      contrib *= 2;
    }
    ans += contrib;

    counts1[V[i]] += 1;
    counts2[pii{g, V[i]}] += 1;
  }
  cout << ans << '\n';
}
