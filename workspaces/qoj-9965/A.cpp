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

  int N;
  cin >> N;

  vc<string> grid(N);
  for (auto &e : grid) cin >> e;

  auto grid2 = grid;
  for (auto &r : grid2) {
    for (auto &e : r) {
      if ('A' <= e and e <= 'Z') {
        e += 'a' - 'A';
      }
    }
  }

  pii deltas[] = {{-1, -1}, {-1, 0}, {-1, 1}, {0, -1},
                  {0, 1},   {1, -1}, {1, 0},  {1, 1}};

  auto is_inside = [&](int i, int j) -> bool {
    return 0 <= i and i < N and 0 <= j and j < N;
  };

  auto is_seen = [&](char x) -> bool { return 'A' <= x and x <= 'Z'; };

  auto normalize = [&](char x) -> char {
    if (!is_seen(x)) return x;
    return x + 'a' - 'A';
  };

  auto is_ok = [&](char a, char b) -> bool {
    a = normalize(a);
    b = normalize(b);
    return (a == 'm' and b == 'p') or (a == 'p' and b == 'm') or
           (a == 'o' and b == 'o');
  };

  queue<pii> q;
  auto push = [&](int i, int j) -> void {
    if (is_seen(grid2[i][j])) return;
    grid2[i][j] += 'A' - 'a';
    q.emplace(i, j);
  };
  rep(i, 0, N) {
    rep(j, 0, N) {
      if (!is_seen(grid[i][j])) continue;
      push(i, j);
    }
  }
  while (sz(q) > 0) {
    auto [i, j] = q.front();
    q.pop();
    for (auto [di, dj] : deltas) {
      int i2 = i + di, j2 = j + dj;
      if (!is_inside(i2, j2)) continue;
      if (!is_ok(grid2[i][j], grid2[i2][j2])) continue;
      push(i2, j2);
    }
  }
  auto count = [&](vc<string> grid) -> int {
    int rv = 0;
    rep(i, 0, N) {
      rep(j, 0, N) {
        if (!is_seen(grid[i][j])) continue;
        rv++;
        for (auto [di, dj] : deltas) {
          if (di < 0 or (di == 0 and dj < 0)) continue;
          int i2 = i + di, j2 = j + dj;
          if (!is_inside(i2, j2)) continue;
          if (!is_seen(grid[i2][j2])) continue;
          if (!is_ok(grid[i][j], grid[i2][j2])) continue;
          rv++;
        }
      }
    }
    return rv;
  };
  cout << count(grid) << ' ' << count(grid2) << '\n';
  for (auto e : grid2) {
    cout << e << '\n';
  }
}
