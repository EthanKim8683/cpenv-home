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

    vc<vc<pii>> adj(N);
    vc deg(N, vi(2, 0));
    rep(i, 0, M) {
      int o, a, b;
      cin >> o >> a >> b;
      o--, a--, b--;
      adj[a].eb(b, o);
      adj[b].eb(a, o);
      deg[a][o]++;
      deg[b][o]++;
    }

    queue<int> q;
    vc<bool> pushed(N, false);
    auto nudge = [&](int a) -> void {
      if (pushed[a]) return;
      if (deg[a][0] != 0 and deg[a][1] != 0) return;
      q.push(a);
      pushed[a] = true;
    };
    rep(i, 0, N) { nudge(i); }
    vi order, sign(N);
    while (sz(q) > 0) {
      int a = q.front();
      q.pop();
      if (deg[a][0] == 0) {
        sign[a] = -1;
      } else {
        sign[a] = 1;
      }
      order.pb(a);
      for (auto [b, o] : adj[a]) {
        deg[b][o]--;
        nudge(b);
      }
    }
    if (sz(order) < N) {
      cout << "NO\n";
      continue;
    }

    vi ans(N);
    rep(i, 0, N) {
      int j = order[i];
      ans[j] = sign[j] * (N - i);
    }
    cout << "YES\n";
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
