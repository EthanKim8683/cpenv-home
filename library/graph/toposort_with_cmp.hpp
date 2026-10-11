std::vector<int> toposort(const std::vector<std::vector<int>> &adj,
                          const std::function<bool(int, int)> &cmp) {
  int n = adj.size();

  std::vector<int> degree(n, 0);
  for (auto adja : adj) {
    for (auto b : adja) {
      degree[b]++;
    }
  }

  auto rcmp = [&](int a, int b) -> bool { return cmp(b, a); };
  std::priority_queue<int, std::vector<int>, decltype(rcmp)> pq(rcmp);
  auto nudge = [&](int a) -> void {
    if (degree[a] != 0) return;
    pq.push(a);
  };
  for (int i = 0; i < n; i++) {
    nudge(i);
  }
  std::vector<int> rv;
  while (pq.size() > 0) {
    int a = pq.top();
    pq.pop();
    rv.push_back(a);
    for (auto b : adj[a]) {
      if (degree[b] == 0) continue;
      degree[b]--;
      nudge(b);
    }
  }
  return rv;
}
