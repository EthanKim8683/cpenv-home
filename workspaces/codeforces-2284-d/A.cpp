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

  string t;
  cin >> t;

  if (t == "first") {
    int T;
    cin >> T;

    while (T--) {
      int N;
      cin >> N;

      string S;
      cin >> S;

      vc<pii> edges;
      if (find(all(S), '1') == S.end()) {
        rep(i, 0, N) {
          rep(j, i + 1, N) { edges.eb(i, j); }
        }
      } else {
        int j;
        rep(i, 0, N - 1) {
          if (S[i] == '1') {
            edges.eb(i, N - 1);
            j = i;
          }
        }
        rep(i, 0, N - 1) {
          if (S[i] == '0') {
            edges.eb(i, j);
          }
        }
      }
      cout << sz(edges) << '\n';
      for (auto [u, v] : edges) {
        cout << u + 1 << ' ' << v + 1 << '\n';
      }
    }
  } else {
    int T;
    cin >> T;

    while (T--) {
      int N, M;
      cin >> N >> M;

      vc<vi> adj(N);
      rep(i, 0, M) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
      }

      if (M > N - 1) {
        cout << string(N - 1, '0') << '\n';
        continue;
      }

      vi colors(N, -1);
      auto dfs = [&](auto self, int a, int c) -> void {
        if (colors[a] != -1) return;
        colors[a] = c;
        for (auto b : adj[a]) {
          self(self, b, c ^ 1);
        }
      };
      dfs(dfs, N - 1, 0);
      rep(i, 0, N - 1) { cout << (char) ('0' + colors[i]); }
      cout << '\n';
    }
  }
}
