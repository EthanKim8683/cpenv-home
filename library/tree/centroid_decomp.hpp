// Returns a rooted tree corresponding to the centroid decomposition
// O(N\log(N))
std::pair<int, std::vector<std::vector<int>>> centroid_decomp(
    const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<bool> cut(n, false);
  std::vector<int> size(n);
  auto dfs_size = [&](auto self, int a, int p) -> int {
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      size[a] += self(self, b, a);
    }
    return size[a];
  };

  auto dfs_find = [&](auto self, int a, int p, int k) -> int {
    for (auto b : adj[a]) {
      if (b == p or cut[b]) continue;
      if (size[b] * 2 > k) {
        return self(self, b, a, k);
      }
    }
    return a;
  };

  std::vector<std::vector<int>> adj2(n);
  auto dfs_build = [&](auto self, int a) -> int {
    a = dfs_find(dfs_find, a, -1, dfs_size(dfs_size, a, -1));
    cut[a] = true;
    for (auto b : adj[a]) {
      if (cut[b]) continue;
      adj2[a].push_back(self(self, b));
    }
    return a;
  };
  int r = dfs_build(dfs_build, 0);
  return {r, adj2};
}
