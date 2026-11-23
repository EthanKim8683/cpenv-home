vc<bool> cut(N, false);
vi size(N);
auto dfs1 = [&](auto self, int a, int p) -> int {
  size[a] = 1;
  for (auto b : adj[a]) {
    if (b == p or cut[b]) continue;
    size[a] += self(self, b, a);
  }
  return size[a];
};

auto dfs2 = [&](auto self, int a, int p, int n) -> int {
  for (auto b : adj[a]) {
    if (b == p or cut[b]) continue;
    if (size[b] * 2 > n) return self(self, b, a, n);
  }
  return a;
};

auto dfs3 = [&](auto self, int a) -> void {
  a = dfs2(dfs2, a, -1, dfs1(dfs1, a, -1));
  cut[a] = true;
  for (auto b : adj[a]) {
    if (cut[b]) continue;
    self(self, b);
  }
};
