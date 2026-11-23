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
vc<S> rrdp(const vc<vi> &adj, T nil,
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
  return dp;
}

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

    using S = int;
    using T = pair<bool, int>;
    auto dp = rrdp<S, T>(
        adj, {false, 0},
        [&](S dp, int a, int i) -> T {
          if (dp == 2) return {true, 0};
          return {false, 1};
        },
        [&](T tdp1, T tdp2) -> T {
          return {tdp1.fs or tdp2.fs, tdp1.sd + tdp2.sd};
        },
        [&](T tdp, int a) -> S {
          if (tdp.fs) return 1;
          if (tdp.sd % 2 == 1) return 2;
          return 0;
        });
    vi ans;
    rep(i, 0, N) {
      if (dp[i] == 0) {
        ans.pb(i);
      }
    }
    if (sz(ans) == 0) {
      cout << "Alice\n";
    } else {
      cout << "Bob\n";
      cout << sz(ans) << '\n';
      for (auto e : ans) {
        cout << e + 1 << ' ';
      }
      cout << '\n';
    }
  }
}
