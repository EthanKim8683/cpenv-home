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

template <typename S, typename T>
pair<vc<S>, vc<vc<T>>> rrdp(const vc<vi> &adj, T nil,
                            auto trans,    // (dp, a, i) -> tdp
                            auto merge,    // (tdp, tdp) -> tdp
                            auto finalize  // (tdp, a) -> dp
) {
  int n = sz(adj);

  vi order(n);
  vc<pii> par(n);
  auto dfs = [&](auto self, int a, int p) -> void {
    order.pb(a);
    rep(i, 0, sz(adj[a])) {
      int b = adj[a][i];
      if (b == p) {
        par[a] = {p, i};
        continue;
      }
      self(self, b, a);
    }
  };
  dfs(dfs, 0, -1);

  vc<S> dp(n);
  vc<T> ddp(n);
  vc<vc<T>> tdp(n);
  reverse(all(order));
  for (auto a : order) {
    tdp[a].resize(sz(adj[a]));
    ddp[a] = nil;
    rep(i, 0, sz(adj[a])) {
      int b = adj[a][i];
      if (b == par[a].fs) continue;
      tdp[a][i] = trans(dp[b], a, i);
      ddp[a] = merge(ddp[a], tdp[a][i]);
    }
    dp[a] = finalize(ddp[a], a);
  }

  vc<T> pdp(n, nil), sdp(n, nil);
  reverse(all(order));
  for (auto a : order) {
    rep(i, 0, sz(adj[a]) - 1) { pdp[i + 1] = merge(pdp[i], tdp[a][i]); }
    sdp[sz(adj[a]) - 1] = nil;
    for (int i = sz(adj[a]) - 1; i >= 1; --i) {
      sdp[i - 1] = merge(tdp[a][i], sdp[i]);
    }
    rep(i, 0, sz(adj[a])) {
      int b = adj[a][i];
      if (b == par[a].fs) continue;
      int j = par[b].sd;
      tdp[b][j] = trans(finalize(merge(pdp[i], sdp[i]), a), b, j);
      dp[b] = finalize(merge(ddp[b], tdp[b][j]), b);
    }
  }
  return {dp, tdp};
}

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // look at invariants or create invariant:
  //
  // must be able to decompose a tree into odd path depth
  //
  // opponent can always just play one edge
  //
  // winning subtree is a rooted subtree with a path from root to a node
  //
  // if a tree has two winning child subtrees, it loses because it can't
  // eliminate both
  //
  // this means that a rooted winning tree has exactly one path that gives it a
  // win
  //
  // we basically just need to pick paths such that remaining subtrees are not
  // winning

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      adj[a].pb(b);
      adj[b].pb(a);
    }

    using S = bool;
    using T = int;
    auto [dp, tdp] = rrdp<S, T>(
        adj, 0, [&](S dp, int a, int i) -> T { return dp ? 1 : 0; },
        [&](T tdp1, T tdp2) -> T { return tdp1 + tdp2; },
        [&](T tdp, int a) -> S { return tdp < 2; });

    rep(i, 0, N) {
      cerr << i << ": ";
      rep(j, 0, sz(adj[i])) {
        if (tdp[i][j] == 0) continue;
        cerr << adj[i][j] << ' ';
      }
      cerr << '\n';
    }
    cerr << '\n';

    vc<bool> seen(N, false);
    vi stack;
    int ans = 0;
    auto dfs = [&](auto self, int a, int p) -> void {
      seen[a] = true;
      stack.pb(a);
      if (sz(stack) >= 2) {
        bool ok = true;
        for (auto e : stack) {
          rep(i, 0, sz(adj[e])) {
            if (seen[adj[e][i]]) continue;
            ok = ok and tdp[e][i] == 0;
          }
        }
        if (ok) {
          ans += 1;
        }
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
      stack.pop_back();
      seen[a] = false;
    };
    rep(i, 0, N) { dfs(dfs, i, -1); }
    cout << ans / 2 << '\n';
  }
}
