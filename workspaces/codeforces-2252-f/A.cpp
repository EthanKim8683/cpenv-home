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

vc<tuple<int, int, int>> virtual_tree(auto index, auto lca, auto is_anc,
                                      auto dist, vi v) {
  auto cmp = [&](int a, int b) -> bool { return index(a) < index(b); };
  sort(all(v), cmp);
  int n = sz(v);
  rep(i, 0, n - 1) { v.pb(lca(v[i], v[i + 1])); }
  sort(all(v), cmp);
  v.erase(unique(all(v)), v.end());

  vc<tuple<int, int, int>> rv;
  auto push = [&](int a, int b) -> void { rv.eb(a, b, dist(a, b)); };
  vi stack;
  for (auto a : v) {
    while (sz(stack) >= 2 and !is_anc(stack.back(), a)) {
      push(stack.end()[-2], stack.back());
      stack.pop_back();
    }
    stack.pb(a);
  }
  while (sz(stack) >= 2) {
    push(stack.end()[-2], stack.back());
    stack.pop_back();
  }
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // if k_c = 1, then optimal solution is always if the component was in a
  // centroid
  //
  // can we greedily expand in the direction of the costliest subtree? yes
  //
  // technically i could solve this as an evil ds problem, but can i do better?
  // i could create virtual trees and then do centroid on that and it would be
  // like O(N\log(N)) total. and expanding in the direction of costliest subtree
  // is just an additional O(N\log(N)) i believe. honestly i think this is the
  // way. it's just modified virtual tree.

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi C(N);
    for (auto &e : C) {
      cin >> e;
      e--;
    }

    vi K(N);
    for (auto &e : K) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vc<vi> by_color(N);
    rep(i, 0, N) { by_color[C[i]].pb(i); }

    vc anc(N, vi(LOGN));
    vi tin(N), tout(N);
    vi depth(N);
    int t = 0;
    auto dfs = [&](auto self, int a, int p) -> void {
      anc[a][0] = p;
      tin[a] = t++;
      for (auto b : adj[a]) {
        if (b == p) continue;
        depth[b] = depth[a] + 1;
        self(self, b, a);
      }
      tout[a] = t;
    };
    depth[0] = 0;
    dfs(dfs, 0, 0);
    rep(i, 1, LOGN) {
      rep(j, 0, N) { anc[j][i] = anc[anc[j][i - 1]][i - 1]; }
    }

    vc<vc<pii>> adj2(N);
    vi size(N);
    auto index = [&](int a) -> int { return tin[a]; };
    auto is_anc = [&](int a, int b) -> int {
      return tin[a] <= tin[b] and tout[b] <= tout[a];
    };
    auto lca = [&](int a, int b) -> int {
      if (is_anc(a, b)) return a;
      if (is_anc(b, a)) return b;
      for (int i = LOGN - 1; i >= 0; i--) {
        if (!is_anc(anc[a][i], b)) {
          a = anc[a][i];
        }
      }
      return anc[a][0];
    };
    auto dist = [&](int a, int b) -> int {
      return depth[a] + depth[b] - 2 * depth[lca(a, b)];
    };
    rep(i, 0, N) {
      if (by_color[i].empty()) {
        cout << "-1 ";
        continue;
      }

      auto edges = virtual_tree(index, lca, is_anc, dist, by_color[i]);
      for (auto [a, b, w] : edges) {
        adj2[a].eb(b, w);
        adj2[b].eb(a, w);
      }

      auto dfs2 = [&](auto self, int a, int p) -> void {
        size[a] = C[a] == i ? 1 : 0;
        for (auto [b, w] : adj2[a]) {
          if (b == p) continue;
          self(self, b, a);
          size[a] += size[b];
        }
      };
      auto dfs3 = [&](auto self, int a, int p, int n) -> int {
        for (auto [b, w] : adj2[a]) {
          if (b == p) continue;
          if (2 * size[b] > n) return self(self, b, a, n);
        }
        return a;
      };
      int a = by_color[i][0];
      dfs2(dfs2, a, -1);
      a = dfs3(dfs3, a, -1, size[a]);

      dfs2(dfs2, a, -1);
      int ans = 0;
      vc<pii> savings;
      auto dfs4 = [&](auto self, int a, int p, int d) -> void {
        ans += C[a] == i ? d : 0;
        for (auto [b, w] : adj2[a]) {
          if (b == p) continue;
          self(self, b, a, d + w);
          savings.eb(size[b], w);
        }
      };
      dfs4(dfs4, a, -1, 0);
      sort(all(savings));
      rep(j, 0, K[i] - 1) {
        if (savings.empty()) break;
        auto &[n, k] = savings.back();
        ans -= n;
        k--;
        if (k == 0) {
          savings.pop_back();
        }
      }
      cout << ans << ' ';

      for (auto [a, b, w] : edges) {
        adj2[a].clear();
        adj2[b].clear();
      }
    }
    cout << '\n';
  }
}
