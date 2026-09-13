template <typename T, typename S>
vc<T> rrdp(const vc<vi> &adj, S nil,
           auto trans,    // function<S(T, int, int)>
           auto merge,    // function<S(S, S)>
           auto finalize  // function<T(S, int)>
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

  vc<T> dp(n);
  vc<S> ddp(n);
  vc<vc<S>> tdp(n);
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

  vc<S> pdp(n, nil), sdp(n, nil);
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
