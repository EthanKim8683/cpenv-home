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

  int T;
  cin >> T;

  while (T--) {
    int R, C;
    cin >> R >> C;

    vc<string> A(R);
    for (auto &e : A) cin >> e;

    vc<string> B(R);
    for (auto &e : B) cin >> e;

    auto encode = [&](int i, int j) -> int { return i * C + j; };

    auto decode = [&](int x) -> pii { return {x / C, x % C}; };

    int s1, s2, d;
    rep(i, 0, R) {
      rep(j, 0, C) {
        if (A[i][j] == 'S') {
          s1 = encode(i, j);
        }
        if (B[i][j] == 'S') {
          s2 = encode(i, j);
        }
        if (B[i][j] == 'D') {
          d = encode(i, j);
        }
      }
    }

    pii deltas[] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    auto is_inside = [&](int i, int j) -> bool {
      return 0 <= i and i < R and 0 <= j and j < C;
    };

    auto is_reachable = [&](vc<string> &grid, int i, int j) -> bool {
      return is_inside(i, j) and grid[i][j] != 'X';
    };

    vc dist(R * C, vi(R * C, INF));
    queue<pii> q;
    auto push = [&](int a1, int a2, int d) -> void {
      if (d >= dist[a1][a2]) return;
      dist[a1][a2] = d;
      q.emplace(a1, a2);
    };
    push(s1, s2, 0);
    while (sz(q) > 0) {
      auto [a1, a2] = q.front();
      q.pop();
      auto [i1, j1] = decode(a1);
      auto [i2, j2] = decode(a2);
      for (auto [di, dj] : deltas) {
        if (!is_reachable(A, i1 + di, j1 + dj)) continue;
        int i3 = i2, j3 = j2;
        if (is_reachable(B, i3 + di, j3 + dj)) {
          i3 += di;
          j3 += dj;
        }
        push(encode(i1 + di, j1 + dj), encode(i3, j3), dist[a1][a2] + 1);
      }
    }
    int ans = INF;
    rep(i, 0, R * C) { chmin(ans, dist[i][d]); }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
