// Euler tour and binary lifting-based tree utils
// TODO:
// - O(1) RMQ LCA (or see https://codeforces.com/blog/entry/153134)
// - O(1) kth ancestor (ladder)
// - Built-in HLD
struct tree_utils {
 private:
  const std::vector<std::vector<int>> &adj;
  int n, logn;
  int r;
  std::vector<int> in, out;
  std::vector<int> depth;
  std::vector<std::vector<int>> anc;

 public:
  tree_utils(const std::vector<std::vector<int>> &_adj, int _r = 0)
      : adj(_adj),
        n(adj.size()),
        logn(std::__lg(n) + 1),
        r(_r),
        in(n),
        out(n),
        depth(n),
        anc(n, std::vector<int>(logn)) {
    int t = 0;
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      in[a] = t++;
      anc[a][0] = p;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
      out[a] = t;
    };
    dfs(dfs, r, r, 0);

    for (int i = 1; i < logn; i++) {
      for (int j = 0; j < n; j++) {
        anc[j][i] = anc[anc[j][i - 1]][i - 1];
      }
    }
  }

  int get_index(int a) const { return in[a]; }
  std::pair<int, int> get_range(int a) const { return {in[a], out[a]}; }

  int get_depth(int a) const { return depth[a]; }

  int get_parent(int a) const {
    assert(a != r);
    return anc[a][0];
  }

  bool is_anc(int a, int b) const {
    return in[a] <= in[b] and out[a] >= out[b];
  }

  int lca(int a, int b) const {
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;

    for (int i = logn - 1; i >= 0; i--) {
      if (!is_anc(anc[a][i], b)) {
        a = anc[a][i];
      }
    }
    return anc[a][0];
  }

  int dist(int a, int b) const {
    return depth[a] + depth[b] - 2 * depth[lca(a, b)];
  }

  int kth_anc(int a, int k) const {
    assert(0 <= k and k <= depth[a]);
    for (int i = logn - 1; i >= 0; i--) {
      if (k >> i & 1) {
        a = anc[a][i];
      }
    }
    return a;
  }

  int kth_on_path(int a, int b, int k) const {
    assert(0 <= k and k <= dist(a, b));
    int c = lca(a, b);
    if (k <= dist(a, c)) {
      return kth_anc(a, k);
    } else {
      return kth_anc(b, dist(a, b) - k);
    }
  }

  bool is_on_path(int a, int b, int c) const {
    return is_anc(lca(a, b), c) and (is_anc(c, a) or is_anc(c, b));
  }

  bool is_in_subtree(int a, int b, int r) const { return is_on_path(r, b, a); }
  bool is_in_subtree(int a, int b) const { return is_in_subtree(a, b, r); }

  // https://www.youtube.com/watch?v=czySm7bUHgY
  // Returns the root and edges of a virtual tree containing the given vertices
  // O(V\log(V))
  std::pair<int, std::vector<std::pair<int, int>>> virtual_tree(
      std::vector<int> v) const {
    int k = v.size();
    assert(k > 0);

    auto cmp = [&](int a, int b) -> bool { return in[a] < in[b]; };
    sort(v.begin(), v.end(), cmp);
    for (int i = 0; i + 1 < k; i++) {
      v.push_back(lca(v[i], v[i + 1]));
    }
    sort(v.begin(), v.end(), cmp);
    v.erase(unique(v.begin(), v.end()), v.end());

    std::vector<int> stack;
    std::vector<std::pair<int, int>> rv;
    for (auto a : v) {
      while (stack.size() >= 2 and !is_anc(stack.back(), a)) {
        rv.push_back({stack.end()[-2], stack.back()});
        stack.pop_back();
      }
      stack.push_back(a);
    }
    while (stack.size() >= 2) {
      rv.push_back({stack.end()[-2], stack.back()});
      stack.pop_back();
    }
    return {stack[0], rv};
  }

  std::vector<int> subtree(int r) {
    std::vector<int> rv;
    auto dfs = [&](auto self, int a, int p) -> void {
      rv.push_back(a);
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs(dfs, r, anc[r][0]);
    return rv;
  }
};
