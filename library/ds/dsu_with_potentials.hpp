template <class S, auto op, auto inv>
struct dsu_with_potentials {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
				  "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(inv), std::function<S(S)>>,
				  "inv must work as S(S)");

   private:
	std::vector<int> root;
	std::vector<S> V;

   public:
	dsu_with_potentials() {}
	dsu_with_potentials(int n, S nil) : root(n, -1), V(n, nil) {}

	int leader(int a) {
		if (root[a] < 0) return a;
		int p = leader(root[a]);
		V[a] = op(V[a], V[root[a]]);
		return root[a] = p;
	}

	bool merge(int a, int b, S v) {
		int a2 = leader(a), b2 = leader(b);
		if (a2 == b2) return op(V[b], inv(V[a])) == v;
		if (root[a2] > root[b2]) {
			std::swap(a2, b2);
			std::swap(a, b);
			v = inv(v);
		}
		root[a2] += root[b2];
		root[b2] = a2;
		V[b2] = op(op(v, V[a]), inv(V[b]));
		return true;
	}

	bool same(int a, int b) { return leader(a) == leader(b); }

	int size(int a) { return -root[leader(a)]; }

	S potential(int a) {
		leader(a);
		return V[a];
	}

	S voltage(int a, int b) { return op(potential(b), inv(potential(a))); }
};
