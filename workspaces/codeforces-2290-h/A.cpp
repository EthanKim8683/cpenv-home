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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi size(N);
    auto dfs = [&](auto self, int a, int p) -> void {
      size[a] = 1;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        size[a] += size[b];
      }
    };
    dfs(dfs, 0, -1);

    auto check = [&](int x) -> bool {
      auto dfs = [&](auto self, int a, int p) -> bool {
        int b2 = -1;
        for (auto b : adj[a]) {
          if (b == p) continue;
          if (size[b] <= x) continue;
          if (b2 != -1) return false;
          b2 = b;
        }
        if (b2 == -1) return true;
        return self(self, b2, a);
      };
      int count = 0;
      bool ok = true;
      for (auto b : adj[0]) {
        if (size[b] <= x) continue;
        ok = ok and dfs(dfs, b, 0);
        count++;
      }
      return ok and count <= 2;
    };
    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << N - l << '\n';
  }
}
