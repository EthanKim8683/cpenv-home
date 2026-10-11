// Returns all (one or two) centroids of the tree
// O(N)
std::vector<int> find_centroids(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };
  dfs_size(dfs_size, 0, -1);

  std::vector<int> rv;
  auto dfs_find = [&](auto self, int a, int p) -> void {
    for (auto b : adj[a]) {
      if (b == p) continue;
      if (size[b] * 2 > n) {
        return self(self, b, a);
      } else if (size[b] * 2 == n) {
        rv.push_back(b);
      }
    }
    rv.push_back(a);
  };
  dfs_find(dfs_find, 0, -1);
  return rv;
}
