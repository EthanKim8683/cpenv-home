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

pair<int, vi> hungarian(const vc<vi> &a) {
  if (a.empty()) return {0, {}};
  int n = sz(a) + 1, m = sz(a[0]) + 1;
  vi u(n), v(m), p(m), ans(n - 1);
  rep(i, 1, n) {
    p[0] = i;
    int j0 = 0;  // add "dummy" worker 0
    vi dist(m, LLONG_MAX), pre(m, -1);
    vc<bool> done(m + 1);
    do {  // dijkstra
      done[j0] = true;
      int i0 = p[j0], j1, delta = LLONG_MAX;
      rep(j, 1, m) if (!done[j]) {
        auto cur = a[i0 - 1][j - 1] - u[i0] - v[j];
        if (cur < dist[j]) dist[j] = cur, pre[j] = j0;
        if (dist[j] < delta) delta = dist[j], j1 = j;
      }
      rep(j, 0, m) {
        if (done[j])
          u[p[j]] += delta, v[j] -= delta;
        else
          dist[j] -= delta;
      }
      j0 = j1;
    } while (p[j0]);
    while (j0) {  // update alternating path
      int j1 = pre[j0];
      p[j0] = p[j1], j0 = j1;
    }
  }
  rep(j, 1, m) if (p[j]) ans[p[j] - 1] = j - 1;
  return {-v[0], ans};  // min cost
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc amounts(N, vi(M));
  for (auto &r : amounts) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  vc adj(N, vi(N));
  for (auto &r : adj) {
    for (auto &e : r) {
      cin >> e;
      if (e == -1) {
        e = INF;
      }
    }
  }

  rep(i, 0, N) {
    rep(j, 0, N) {
      rep(k, 0, N) { chmin(adj[j][k], adj[j][i] + adj[i][k]); }
    }
  }

  vc costs(M, vi(N, 0));
  rep(i, 0, M) {
    rep(j, 0, N) {
      rep(k, 0, N) { costs[i][j] += amounts[k][i] * adj[k][j]; }
    }
  }
  cout << hungarian(costs).fs << '\n';
}
