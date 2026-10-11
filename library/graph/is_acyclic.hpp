bool is_acyclic(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  auto order = toposort(adj);
  std::vector<bool> seen(n, false);
  for (auto a : order) {
    seen[a] = true;
    for (auto b : adj[a]) {
      if (seen[b]) return false;
    }
  }
  return true;
}
