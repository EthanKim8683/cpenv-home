#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int) (x).size()
#define eb emplace_back
#define pb push_back
#define vc vector
#define fs first
#define sd second
typedef pair<int, int> pii;
typedef vc<int> vi;

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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) cin >> e;

    auto [r, adj] = cartesian_tree(P);
  }
}
