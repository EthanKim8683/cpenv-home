// https://cp-algorithms.com/graph/bridge-searching.html
std::vector<std::pair<int, int>> find_bridges(
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> seen(n, false);
  std::vector<int> tin(n), tmin(n);
  std::vector<std::pair<int, int>> rv;
  int t = 0;
  auto dfs = [&](auto self, int a, int p) -> void {
    seen[a] = true;
    tin[a] = tmin[a] = t++;
    bool skipped = false;
    for (auto b : adj[a]) {
      if (b == p and !skipped) {
        skipped = true;
        continue;
      }
      if (seen[b]) {
        tmin[a] = std::min(tmin[a], tin[b]);
      } else {
        self(self, b, a);
        tmin[a] = std::min(tmin[a], tmin[b]);
        if (tmin[b] > tin[a]) {
          int u = a, v = b;
          if (u > v) {
            std::swap(u, v);
          }
          rv.push_back({u, v});
        }
      }
    }
  };
  for (int i = 0; i < n; i++) {
    if (seen[i]) continue;
    dfs(dfs, 0, -1);
  }
  return rv;
}
