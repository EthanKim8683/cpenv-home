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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vc<pii> queries(Q);
    for (auto &[a, b] : queries) {
      cin >> a >> b;
      a--, b--;
    }

    vc<vc<pii>> queries2(N + 1);
    rep(i, 0, Q) {
      auto [a, b] = queries[i];
      queries2[N - a].eb(b - a, i);
      queries2[b + 1].eb(b - a, i);
    }

    vi dist(N, INF), ans(Q, 4);
    rep(i, 0, N) {
      int d = INF;
      if (i == 0) {
        d = 0;
      } else {
        for (int j = 1; i - j * j >= 0; j++) {
          chmin(d, dist[i - j * j] + 1);
        }
      }

      auto dfs = [&](auto self, int a, int d) -> void {
        if (d >= dist[a]) return;
        dist[a] = d;
        for (int j = 1; a - j * j >= 0; j++) {
          self(self, a - j * j, dist[a] + 1);
        }
        for (int j = 1; a + j * j <= i; j++) {
          self(self, a + j * j, dist[a] + 1);
        }
      };
      dfs(dfs, i, d);

      for (auto [j, k] : queries2[i + 1]) {
        chmin(ans[k], dist[j]);
      }
      for (int j = 1; i + 1 - j * j >= 0; j++) {
        for (auto [k, l] : queries2[i + 1 - j * j]) {
          chmin(ans[l], dist[k + j * j] + 1);
        }
      }
    }
    for (auto e : ans) {
      cout << e << '\n';
    }
  }
}
