// vc<int> v -> vc<T> v
// v[i] > v[st.back()] -> above(v[i], v[st.back()])
pair<int, vc<pii>> cartesian_tree(vc<int> v) {
  vc<pii> rv(sz(v), {-1, -1});
  vi st;
  rep(i, 0, sz(v)) {
    while (sz(st) and v[i] > v[st.back()]) {
      rv[i].fs = st.back();
      st.pop_back();
    }
    if (sz(st)) rv[st.back()].sd = i;
    st.pb(i);
  }
  return {st[0], rv};
}
