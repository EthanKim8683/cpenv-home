// include "./sos.hpp"
// include "./rsos.hpp"

vi orconv(vi a, vi b) {
	sos(a), sos(b);
	vi c(sz(a));
	rep(i, 0, sz(c)) c[i] = a[i] * b[i];
	rsos(c);
	return c;
}
