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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // maybe go by their lca? this means A and B are in subtrees of different
  // children of lca
  //
  // for A, outline the virtual tree. it's effectively twice the number of edges
  // in the virtual tree containing root
  //
  // we need to add nodes to each other's virtual trees such that they are
  // "compatible". what makes them "compatible"? "compatible" means all nodes in
  // A and B are distance at most d from their intersection
  //
  // take their base intersection, then add branches to the intersection to make
  // it closer to the needed nodes. because the intersection always goes up to
  // root, i imagine we could always add the dth parent of every node

  int N, D;
  cin >> N >> D;

  vc<vi> adj(N);
  rep(i, 0, N - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  int M1;
  cin >> M1;

  vi A(M1);
  for (auto &e : A) {
    cin >> e;
    e--;
  }

  int M2;
  cin >> M2;

  vi B(M2);
  for (auto &e : B) {
    cin >> e;
    e--;
  }

  vc anc(N, vi(LOGN + 1));
  auto dfs = [&](auto self, int a, int p) -> void {
    anc[a][0] = p;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
    }
  };
  dfs(dfs, 0, 0);
  rep(i, 1, LOGN) {
    rep(j, 0, N) { anc[j][i] = anc[anc[j][i - 1]][i - 1]; }
  }
  auto kth_anc = [&](int a, int k) -> int {
    for (int i = LOGN; i >= 0; i--) {
      if ((1ll << i) > k) continue;
      a = anc[a][i];
      k -= 1ll << i;
    }
    return a;
  };

  vc<bool> used(N, false);
  auto dfs2 = [&](auto self, int a, int p) -> int {
    int rv = 0;
    for (auto b : adj[a]) {
      if (b == p) continue;
      rv += self(self, b, a);
      if (used[b]) {
        used[a] = true;
        rv += 1;
      }
    }
    return rv;
  };
  for (auto e : A) {
    used[e] = true;
  }
  for (auto e : B) {
    used[kth_anc(e, D)] = true;
  }
  int ans = dfs2(dfs2, 0, -1);
  fill(all(used), false);
  for (auto e : B) {
    used[e] = true;
  }
  for (auto e : A) {
    used[kth_anc(e, D)] = true;
  }
  ans += dfs2(dfs2, 0, -1);
  ans *= 2;
  cout << ans << '\n';
}
