struct FT {
	vi s;
	FT(int n) : s(n) {}
	void update(int i, int dif) {  // a[i] += dif
		for (; i < sz(s); i |= i + 1) s[i] += dif;
	}
	int query(int i) {	// sum of values in [0, i)
		int r = 0;
		for (; i > 0; i &= i - 1) r += s[i - 1];
		return r;
	}
	int lower_bound(int sum) {	// min i st sum of [0, i] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		// (assumes a[i] >= 0)
		if (sum <= 0) return -1;
		int i = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (i + pw <= sz(s) && s[i + pw - 1] < sum)
				i += pw, sum -= s[i - 1];
		}
		return i;
	}
};
