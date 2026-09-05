void sack(const std::function<void(int)> &insert,
		  const std::function<void()> &clear,
		  const std::function<void(int)> &callback,
		  const std::vector<std::vector<int>> &adj, int r = 0) {
	int n = adj.size();

	std::vector<int> order(n);
	int t = 0;
	auto dfs = [&](auto self, int a, int p) -> void {
		order[t] = a;
		t++;

		int l = t;
		for (int i = 1; i < (int) adj[a].size(); i++) {
			if (adj[a][i] == p) continue;
			self(self, adj[a][i], a);
			clear();
		}
		int r = t;

		if ((int) adj[a].size() > 0 and adj[a][0] != p) {
			self(self, adj[a][0], a);
			for (int i = l; i < r; i++) {
				insert(order[i]);
			}
		}
		insert(a);

		callback(a);
	};
	dfs(dfs, r, -1);
}
