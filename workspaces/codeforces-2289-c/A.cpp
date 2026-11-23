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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

// vc<int> v -> vc<T> v
// v[i] > v[st.back()] -> above(v[i], v[st.back()])
pair<int, vc<pii>> cartesian_tree(vc<int> v) {
  vc<pii> rv(sz(v), {-1, -1});
  vi st;
  rep(i, 0, sz(v)) {
    while (sz(st) and v[i] < v[st.back()]) {
      rv[i].fs = st.back();
      st.pop_back();
    }
    if (sz(st)) rv[st.back()].sd = i;
    st.pb(i);
  }
  return {st[0], rv};
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // the min is either at the end such that moving away loses the min and moving
  // towards encounters a smaller value (min increases or decreases)
  //
  // or both sides has a smaller min (min decreases)
  //
  // or the length is 1 (min increases)
  //
  // think about this with cartesian tree
  //
  // any range between two mins is a good range (case 2)
  //
  // pick a min. if an adjacent is smaller, this is good (case 1)
  //
  // be sure not to double count
  //
  // how to do this cleanly? pick a min. look left and look right. casework:
  //
  // space on left and space on right:
  //   fill fully
  //   just self
  //
  // space on left, none on right (and vice versa):
  //   try all possible space on left
  //
  // none on either:
  //   just self

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) cin >> e;

    auto [m, adj] = cartesian_tree(P);
    int ans = 0;
    auto dfs = [&](auto self, int l, int m, int r) -> void {
      if (m == -1) return;
      if (m - l > 0 and r - (m + 1) > 0) {
        ans += 2;
      } else if (m - l == 0 and r - (m + 1) == 0) {
        ans += 1;
      } else {
        ans += r - l;
      }
      auto [m2, m3] = adj[m];
      self(self, l, m2, m);
      self(self, m + 1, m3, r);
    };
    dfs(dfs, 0, m, N);
    cout << ans << '\n';
  }
}
