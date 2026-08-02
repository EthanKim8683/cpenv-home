struct hld {
  int n;
  vi par, dep, tin, head;
  hld(vc<vi> g, int r) : n(sz(g)), par(n), dep(n), tin(n), head(n) {
    auto dfs = [&](auto self, int a) -> int {
      int s = 1, mx = 0;
      for (int &b : g[a]) {
        erase(g[b], par[b] = a);
        dep[b] = dep[a] + 1;
        int t = self(self, b);
        s += t;
        if (t > mx) swap(b, g[a][0]), mx = t;
      }
      return s;
    };
    par[r] = r, dfs(dfs, r);
    iota(all(head), 0);
    int t = 0;
    auto dfs2 = [&](auto self, int a) -> void {
      tin[a] = t++;
      if (sz(g[a])) head[g[a][0]] = head[a];
      for (auto b : g[a]) self(self, b);
    };
    dfs2(dfs2, r);
  }
  void hl(int a, int b, auto f) {
    for (;; b = par[head[b]]) {
      if (tin[a] > tin[b]) swap(a, b);
      if (head[a] == head[b]) break;
      f(tin[head[b]], tin[b] + 1);
    }
    f(tin[a], tin[b] + 1);
  }
  int lca(int a, int b) {
    while (head[a] != head[b]) {
      int &c = dep[head[a]] > dep[head[b]] ? a : b;
      c = par[head[c]];
    }
    return dep[a] < dep[b] ? a : b;
  }
  int dist(int a, int b) { return dep[a] + dep[b] - 2 * dep[lca(a, b)]; }
  // TODO: sack
};
