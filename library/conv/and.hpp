// include "./sos.hpp"
// include "./rsos.hpp"

vi andconv(vi a, vi b) {
  sos(a, 1), sos(b, 1);
  vi c(sz(a));
  rep(i, 0, sz(c)) c[i] = a[i] * b[i];
  rsos(c, 1);
  return c;
}
