// Returns a hash of the unlabeled unrooted tree
// O(N)
template <long long MOD = (1ll << 61) - 1>
long long tree_hash(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  auto roots = find_centroids(adj);
  std::vector<long long> hashes;
  for (auto r : roots) {
    hashes.push_back(tree_hash<long long, MOD>(adj, r));
  }
  sort(hashes.begin(), hashes.end());

  static long long base = std::mt19937_64(time(nullptr))() % MOD;
  long long rv = 0;
  for (auto e : hashes) {
    rv = ((__int128) rv * base + e) % MOD;
  }
  return rv;
}
