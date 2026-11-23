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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, T;
  cin >> N >> T;

  vc<tuple<int, int, int, int>> trains(T);
  for (auto &[u, v, dep, arr] : trains) {
    cin >> u >> v >> dep >> arr;
    u--, v--;
  }

  vc<tuple<int, int, int>> events;
  rep(i, 0, T) {
    auto [u, v, dep, arr] = trains[i];
    events.eb(dep, 1, i);
    events.eb(arr, 0, i);
  }
  sort(all(events));
  vi dp1(N, INF), dp2(T), dp3(N, INF);
  dp1[0] = 0;
  for (auto [t, s, i] : events) {
    auto [u, v, dep, arr] = trains[i];
    if (s == 1) {
      dp2[i] = dp1[u] + t;
    } else {
      chmin(dp1[v], dp2[i] - t);
      chmin(dp3[v], dp2[i]);
    }
  }
  int ans = dp3[N - 1];
  cout << (ans == INF ? -1 : ans) << '\n';
}
