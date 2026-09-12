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

const int MAXA = 1e9;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // binary search + centroid decomp?
  //
  // maximize # of edges removed
  //
  // if edges removed >= K, then ok
  //
  // how to combine at centroid?
  //
  // for each subtree, search among prev subtrees (sort prevs)
  //
  // i didn't need to do centroid

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi sums(N);
    auto dfs = [&](auto self, int a, int p) -> void {
      sums[a] = A[a];
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        sums[a] += sums[b];
      }
    };
    dfs(dfs, 0, -1);

    vi dp(N);
    vc<pii> stack;
    auto check = [&](int x) -> bool {
      bool rv = false;
      auto dfs2 = [&](auto self, int a, int p) -> void {
        dp[a] = -INF;
        if (sums[a] >= x) {
          chmax(dp[a], 0);
        }
        for (auto b : adj[a]) {
          if (b == p) continue;
          self(self, b, a);
          if (sums[a] - sums[b] >= x) {
            chmax(dp[a], dp[b] + 1);
          }
        }

        stack.clear();
        stack.eb(0, 0);
        int i = 0;
        for (auto b : adj[a]) {
          if (b == p) continue;
          while (i >= 0 and stack[i].fs > sums[0] - sums[b] - x) {
            i--;
          }
          if (i >= 0) {
            rv = rv or stack[i].sd + dp[b] + 1 >= K;
          }
          if (i < sz(stack) - 1) continue;
          if (stack.back().sd >= dp[b] + 1) continue;
          stack.eb(sums[b], dp[b] + 1);
          i++;
        }
      };
      dfs2(dfs2, 0, -1);
      return rv;
    };
    int l = -1, r = sums[0] / (K + 1);
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
