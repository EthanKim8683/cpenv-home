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

template <class S, auto op, auto e>
struct sparse_table {
  int n;
  vc<vc<S>> d;
  sparse_table(const vc<S> &v) : n(sz(v)), d(__lg(n) + 1, vc<S>(n, e())) {
    copy(all(v), d[0].begin());
    rep(i, 1, sz(d)) rep(j, 0, n - (1 << i) + 1) d[i][j] =
        op(d[i - 1][j], d[i - 1][j + (1 << (i - 1))]);
  }
  S prod(int l, int r) {
    if (l >= r) return e();
    int i = __lg(r - l);
    return op(d[i][l], d[i][r - (1 << i)]);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q, T;
  cin >> N >> Q >> T;

  vi A(N);
  for (auto &e : A) cin >> e;

  vc<vi> adj(N);
  rep(i, 0, N - 1) {
    int u, v;
    cin >> u >> v;
    u--, v--;
    adj[u].pb(v);
    adj[v].pb(u);
  }

  // coordinate compress A
  vi cc = A;
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(all(cc), x) - cc.begin();
  };
  for (auto &e : A) {
    e = compress(e);
  }

  // build O(1) lca
  vi tin(N), tout(N);
  vc<pii> pairs;
  auto dfs = [&](auto self, int a, int p, int d) -> void {
    tin[a] = sz(pairs);
    for (auto b : adj[a]) {
      if (b == p) continue;
      pairs.eb(d, a);
      self(self, b, a, d + 1);
    }
    tout[a] = sz(pairs);
  };
  dfs(dfs, 0, -1, 0);
  using S = pii;
  auto op = [&](S a, S b) -> S { return min(a, b); };
  auto e = [&]() -> pii { return {INF, -1}; };
  sparse_table<S, op, e> st(pairs);
  auto lca = [&](int a, int b) -> int {
    int l = tin[a], r = tin[b];
    if (l > r) {
      swap(l, r);
    }
    return st.prod(l + 1, r).sd;
  };
  auto is_anc = [&](int a, int b) -> bool {
    return tin[a] <= tin[b] and tout[b] <= tout[a];
  };

  // build virtual trees
  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> int { return tin[a] < tin[b]; });
  vc<vi> by_A(sz(cc));
  for (auto e : order) {
    by_A[A[e]].pb(e);
  }
  vc<vi> adj2(N);
  vc<unordered_map<int, int>> depths(N);
  rep(i, 0, sz(cc)) {
    vi nodes;
    for (auto e : by_A[i]) {
      if (nodes.empty()) {
        nodes.pb(e);
      } else {
        nodes.pb(lca(nodes.back(), e));
        nodes.pb(e);
      }
    }
    nodes.erase(unique(all(nodes)), nodes.end());

    vi stack;
    for (auto e : nodes) {
      while (sz(stack) >= 2 and !is_anc(stack.back(), e)) {
        adj2[stack.end()[-2]].pb(stack.back());
        stack.pop_back();
      }
      stack.pb(e);
    }
    while (sz(stack) >= 2) {
      adj2[stack.end()[-2]].pb(stack.back());
      stack.pop_back();
    }
    int r = stack[0];

    auto dfs2 = [&](auto self, int a, int d) -> void {
      depths[a][i] = d;
      for (auto b : adj[a]) {
        self(self, b, d + 1);
      }
    };
    dfs2(dfs2, r, 0);

    for (auto e : nodes) {
      adj2[e].clear();
    }
  }
  auto dist = [&](int i, int a, int b) -> int {};
}
