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

    vc<vi> adj(N);
    vi deg(N, 0);
    auto add_edge = [&](int a, int b) -> void {
      adj[a].pb(b);
      deg[b] += 1;
    };
    rep(i, 0, M) {
      int a, b;
      cin >> a >> b;
      a--, b--;
      add_edge(a, b);
    }

    int ans = 0;
    set<int> next;
    rep(i, 0, N) {
      if (deg[i] != 0) continue;
      next.insert(i);
    }
    rep(i, 0, N) {
      if (!next.contains(i)) {
        goto FAIL;
      }

      next.erase(i);
      for (auto e : next) {
        add_edge(e - 1, e);
        ans += 1;
      }
      next.clear();

      for (auto e : adj[i]) {
        deg[e] -= 1;
        if (deg[e] == 0) {
          next.insert(e);
        }
      }
    }
    cout << ans << '\n';

    continue;
  FAIL:
    cout << "-1\n";
  }
}
