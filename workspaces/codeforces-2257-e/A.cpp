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
    int N, X;
    cin >> N >> X;

    vc<pair<vi, vi>> buildings(N);
    for (auto &[costs, profits] : buildings) {
      int m;
      cin >> m;

      costs.resize(m);
      for (auto &e : costs) cin >> e;

      profits.resize(m);
      for (auto &e : profits) cin >> e;
    }

    vc<tuple<int, int, int, int>> gains;
    rep(i, 0, N) {
      auto [costs, profits] = buildings[i];
      int delta = 0, min_delta = 0, max_delta = 0;
      rep(j, 0, sz(costs)) {
        delta -= costs[j];
        chmin(min_delta, delta);
        delta += profits[j];
        if (delta > max_delta) {
          gains.eb(-min_delta, i, j + 1, delta - max_delta);
          max_delta = delta;
        }
      }
    }
    sort(all(gains));

    vi base_heights(N, 0);
    int base_capital = X;
    for (auto [cost, i, j, profit] : gains) {
      if (cost > base_capital) break;
      base_heights[i] = j;
      base_capital += profit;
    }

    pii ans = {0, 0};
    rep(i, 0, N) {
      auto [costs, profits] = buildings[i];
      int capital = base_capital, height = base_heights[i];
      for (; height < sz(costs); height++) {
        capital -= costs[height];
        if (capital < 0) break;
        capital += profits[height];
      }
      chmax(ans, pii{height, -i});
    }
    auto [height, i] = ans;
    cout << height << ' ' << -i + 1 << '\n';
  }
}
