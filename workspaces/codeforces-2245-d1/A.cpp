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
    int N, M;
    cin >> N >> M;

    vc<tuple<int, int, int>> edges;
    vc<bool> gz(N);
    rep(i, 0, M) {
      int o, a, b;
      cin >> o >> a >> b;
      a--, b--;

      if (a == b) {
        gz[a] = o == 1;
      } else {
        edges.eb(a, b, o);
      }
    }

    bool ok = true;
    vc<vi> adj2(N);
    for (auto [a, b, o] : edges) {
      if (gz[a] and gz[b]) {
        ok = ok and o == 1;
      } else if (gz[a]) {
        if (o == 1) {
          adj2[b].pb(a);
        } else {
          adj2[a].pb(b);
        }
      } else if (gz[b]) {
        if (o == 2) {
          adj2[b].pb(a);
        } else {
          adj2[a].pb(b);
        }
      } else {
        ok = ok and o == 2;
      }
    }
    if (!ok) {
      cout << "NO\n";
      continue;
    }

    vc<bool> seen(N, false);
    vi order;
    auto dfs = [&](auto self, int a) -> void {
      if (seen[a]) return;
      seen[a] = true;
      for (auto b : adj2[a]) {
        self(self, b);
      }
      order.pb(a);
    };
    rep(i, 0, N) { dfs(dfs, i); }
    reverse(all(order));
    ok = true;
    fill(all(seen), false);
    for (auto e : order) {
      for (auto b : adj2[e]) {
        ok = ok and !seen[b];
      }
      seen[e] = true;
    }
    if (!ok) {
      cout << "NO\n";
      continue;
    }

    vi ans(N);
    rep(i, 0, N) {
      int j = order[i];
      ans[j] = (gz[j] ? 1 : -1) * (i + 1);
    }
    cout << "YES\n";
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
