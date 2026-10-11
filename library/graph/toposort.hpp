std::vector<int> toposort(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> seen(n, false);
  std::vector<int> rv;
  auto dfs = [&](auto self, int a) -> void {
    if (seen[a]) return;
    seen[a] = true;

    for (auto b : adj[a]) {
      self(self, b);
    }
    rv.push_back(a);
  };
  for (int i = 0; i < n; i++) {
    dfs(dfs, i);
  }
  reverse(rv.begin(), rv.end());
  return rv;
}
