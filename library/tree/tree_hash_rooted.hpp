// https://rng-58.blogspot.com/2017/02/hashing-and-probability-of-collision.html
// Returns a hash of the unlabeled rooted tree
// O(N)
template <long long MOD = (1ll << 61) - 1>
long long tree_hash(const std::vector<std::vector<int>> &adj, int r) {
  int n = adj.size();

  std::vector<int> depth(n);
  auto dfs_depth = [&](auto self, int a, int p) -> void {
    depth[a] = 0;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      depth[a] = std::max(depth[a], depth[b] + 1);
    }
  };
  dfs_depth(dfs_depth, r, -1);

  static std::mt19937_64 rng(time(nullptr));
  static std::vector<long long> vars = {1};
  while ((int) vars.size() < depth[r] + 1) {
    vars.push_back(rng() % MOD);
  }

  auto dfs_hash = [&](auto self, int a, int p) -> long long {
    long long hash = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      hash = (__int128) hash * (vars[depth[a]] + self(self, b, a)) % MOD;
    }
    return hash;
  };
  return dfs_hash(dfs_hash, r, -1);
}
