// https://cp-algorithms.com/graph/pruefer_code.html
// Returns the Prüfer code of a labelled tree
std::vector<int> prufer_code(const std::vector<std::vector<int>> &adj) {
  int n = adj.size();

  std::vector<int> parent(n, -1);
  auto dfs = [&](auto self, int a) -> void {
    for (auto b : adj[a]) {
      if (b == parent[a]) continue;
      self(self, b);
    }
  };
  dfs(dfs, n - 1);

  std::vector<int> degree(n, 0);
  for (int i = 0; i < n; i++) {
    degree[i] = adj[i].size();
  }

  int j = -1;
  for (int i = 0; i < n; i++) {
    if (degree[i] != 1) continue;
    j = i;
    break;
  }

  std::vector<int> rv;
  int a = j;
  for (int i = 0; i < n - 2; i++) {
    int p = parent[a];
    rv.push_back(p);

    degree[p]--;
    if (degree[p] == 1 and p < j) {
      a = p;
    } else {
      do {
        j++;
      } while (degree[j] != 1);
      a = j;
    }
  }
  return rv;
}
