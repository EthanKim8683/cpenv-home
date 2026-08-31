void sos(vi &v, bool sup = 0) {
	rep(i, 0, sz(v)) rep(j, 0, 1 << sz(v))
		if ((j >> i & 1) ^ sup) v[j] += v[j - (1 << i)];
}
