// https://judge.yosupo.jp/submission/339108
struct mbm_graph {
 private:
  int n, m;
  std::vector<std::vector<int>> adj;
  std::vector<int> mate;

 public:
  mbm_graph(int _n, int _m) : n(_n), m(_m), adj(n + m), mate(n + m, -1) {}

  void add_edge(int l, int r) {
    adj[l].push_back(n + r);
    adj[n + r].push_back(l);
  }

  int match() {
    std::queue<int> q1;
    for (int i = n; i < n + m; i++) {
      q1.push(i);
    }
    while (true) {
      std::vector<int> depth(n + m, std::numeric_limits<int>::max());
      std::queue<int> q2;
      for (int i = 0; i < n; i++) {
        if (mate[i] != -1) continue;
        depth[i] = 0;
        q2.push(i);
      }
      while (q2.size() > 0) {
        int a = q2.front();
        q2.pop();

        for (auto b : adj[a]) {
          if (depth[a] + 1 >= depth[b]) continue;
          depth[b] = depth[a] + 1;

          int c = mate[b];
          if (c != -1) {
            depth[c] = depth[b] + 1;
            q2.push(c);
          }
        }
      }

      for (int i = 0; i < n + m; i++) {
        if (q1.empty()) {
          return (n + m - count(mate.begin(), mate.end(), -1)) / 2;
        }

        int a = q1.front();
        q1.pop();

        int d = std::numeric_limits<int>::max(), b;
        for (auto c : adj[a]) {
          if (depth[c] >= d) continue;
          d = depth[c];
          b = c;
        }
        if (d < std::numeric_limits<int>::max()) {
          depth[a] = depth[b] + 1;

          int c = mate[b];
          if (c != -1) {
            mate[c] = -1;
            q1.push(c);
          }

          mate[a] = b;
          mate[b] = a;
          depth[b] += 2;
        }
      }
    }
  }

  std::vector<std::pair<int, int>> matching() {
    std::vector<std::pair<int, int>> rv;
    for (int i = 0; i < n; i++) {
      if (mate[i] == -1) continue;
      rv.push_back({i, mate[i] - n});
    }
    return rv;
  }

  std::vector<std::vector<int>> minimum_chain_cover() {
    assert(n == m);
    std::vector<std::vector<int>> rv;
    for (int i = 0; i < n; i++) {
      if (mate[n + i] != -1) continue;

      std::vector<int> chain;
      int a = i;
      while (a >= 0) {
        chain.push_back(a);
        a = mate[a] - n;
      }
      rv.push_back(chain);
    }
    return rv;
  }
};
