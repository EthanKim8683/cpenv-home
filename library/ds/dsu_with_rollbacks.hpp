struct dsu_with_rollbacks {
   private:
	std::vector<int> root, saves;
	std::vector<std::tuple<int, int, int>> history;

   public:
	dsu_with_rollbacks() {}
	dsu_with_rollbacks(int n) : root(n, -1), saves({0}) {}

	// https://codeforces.com/blog/entry/90340?#comment-787571
	// O(\log(N))
	int leader(int a) {
		if (root[a] < 0) return a;
		return leader(root[a]);
	}

	int merge(int a, int b) {
		if ((a = leader(a)) == (b = leader(b))) return a;
		if (root[a] > root[b]) {
			std::swap(a, b);
		}
		history.push_back({a, b, root[b]});
		root[a] += root[b];
		root[b] = a;
		return a;
	}

	bool same(int a, int b) { return leader(a) == leader(b); }

	int size(int a) { return -root[leader(a)]; }

	void save() { saves.push_back(history.size()); }

	void rollback() {
		while ((int) history.size() > saves.back()) {
			auto [a, b, size] = history.back();
			history.pop_back();
			root[a] -= size;
			root[b] = size;
		}
		saves.pop_back();
	}
};
