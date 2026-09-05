template <class S, auto op, auto e>
struct sparse_table {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
				  "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
				  "e must work as S()");

   private:
	int n;
	std::vector<std::vector<S>> table;

   public:
	sparse_table() {}
	sparse_table(const std::vector<S> &v)
		: n(v.size()), table(std::__lg(n) + 1, std::vector<S>(n, e())) {
		std::copy(v.begin(), v.end(), table[0].begin());
		for (int i = 1; i < (int) table.size(); i++) {
			for (int j = 0; j + (1 << i) <= n; j++) {
				table[i][j] =
					op(table[i - 1][j], table[i - 1][j + (1 << (i - 1))]);
			}
		}
	}

	S prod(int l, int r) const {
		if (l >= r) return e();
		int d = std::__lg(r - l);
		return op(table[d][l], table[d][r - (1 << d)]);
	}
};
