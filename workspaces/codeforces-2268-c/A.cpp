#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

// #define int long long
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

const int LOGA = 18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

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
    if (sz(st) > 0) {
      rv[st.back()].sd = i;
    }
    st.pb(i);
  }
  return {st[0], rv};
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps(N + 1);
    ps[0] = 0;
    rep(i, 0, N) { ps[i + 1] = ps[i] ^ A[i]; }

    vi order;
    auto [r, adj] = cartesian_tree(A);
    vc<unordered_map<int, pii>> maps(N + 1);
    auto dfs = [&](auto self, int m, int l, int r) -> int {
      if (m == -1) {
        maps[l].reserve(1);
        return l;
      }
      int small = self(self, adj[m].fs, l, m),
          large = self(self, adj[m].sd, m + 1, r);
      if (m - l > r - (m + 1)) {
        swap(small, large);
      }
      order.pb(m);
      adj[m] = {small, large};
      maps[large].reserve(r - l + 1);
      return large;
    };
    dfs(dfs, r, 0, N);

    auto check = [&](int x) -> bool {
      rep(i, 0, N + 1) {
        maps[i].clear();
        maps[i][ps[i] & x] = {i, i};
      }

      for (auto e : order) {
        auto [small, large] = adj[e];

        if ((A[e] & x) == x) {
          for (auto [ps, range] : maps[small]) {
            auto it = maps[large].find(x ^ ps);
            if (it == maps[large].end()) continue;
            auto range2 = it->sd;
            if (max(range.sd, range2.sd) - min(range.fs, range2.fs) >= 2) {
              return true;
            }
          }
        }

        for (auto [ps, range] : maps[small]) {
          auto it = maps[large].find(ps);
          if (it == maps[large].end()) {
            maps[large][ps] = range;
          } else {
            auto &range2 = it->sd;
            chmin(range2.fs, range.fs);
            chmax(range2.sd, range.sd);
          }
        }
        maps[small].clear();
      }
      return false;
    };
    int ans = 0;
    for (int i = LOGA - 1; i >= 0; i--) {
      if (check(ans ^ 1 << i)) {
        ans ^= 1 << i;
      }
    }
    cout << ans << '\n';
  }
}
