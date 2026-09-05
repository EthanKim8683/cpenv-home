void sort_hld(std::vector<std::vector<int>> &adj, int r = 0) {
	auto dfs = [&](auto self, int a, int p) -> int {
		int rv = 1, nmax = 0;
		for (int i = 0; i < (int) adj[a].size(); i++) {
			if (adj[a][i] == p) {
				std::swap(adj[a][i], adj[a].back());
			}

			if (adj[a][i] == p) continue;
			int n = self(self, adj[a][i], a);
			rv += n;

			if (i == 0) {
				nmax = n;
			} else {
				if (n > nmax) {
					std::swap(adj[a][0], adj[a][i]);
					nmax = n;
				}
			}
		}
		return rv;
	};
	dfs(dfs, r, -1);
}
