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

const string dirs = "NESW";
const pii deltas[] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int R, C, E;
  cin >> R >> C >> E;
  E--;

  int R1, C1, R2, C2;
  char D1, D2;
  cin >> R1 >> C1 >> D1 >> R2 >> C2 >> D2;
  R1--, C1--, R2--, C2--;

  int N;
  cin >> N;

  vc<pii> hz_walls(N);
  for (auto &[r, c] : hz_walls) {
    cin >> r >> c;
    r--, c--;
  }

  cin >> N;

  vc<pii> vt_walls(N);
  for (auto &[r, c] : vt_walls) {
    cin >> r >> c;
    r--, c--;
  }

  pii dest = {E, -1};

  int dd = ((find(all(dirs), D2) - begin(dirs)) + 4 -
            (find(all(dirs), D1) - begin(dirs))) %
           4;

  vc has_hz_wall(R, vc<bool>(C, false));
  for (auto [r, c] : hz_walls) {
    has_hz_wall[r][c] = true;
  }

  vc has_vt_wall(R, vc<bool>(C, false));
  for (auto [r, c] : vt_walls) {
    has_vt_wall[r][c] = true;
  }

  auto is_inside = [&](pii a) -> bool {
    auto [x, y] = a;
    return 0 <= x and x < R and 0 <= y and y < C;
  };

  auto move = [&](pii a, int d) -> pair<pii, int> {
    if (a == dest) return {a, 0};
    auto [x, y] = a;
    auto [dx, dy] = deltas[d];
    pii b = {x + dx, y + dy};
    if (b == dest) return {b, 0};
    if (!is_inside(b)) return {a, 1};
    if (d == 0 and has_hz_wall[a.fs][a.sd]) return {a, 1};
    if (d == 1 and has_vt_wall[a.fs][a.sd]) return {a, 1};
    if (d == 2 and has_hz_wall[b.fs][b.sd]) return {a, 1};
    if (d == 3 and has_vt_wall[b.fs][b.sd]) return {a, 1};
    return {b, 0};
  };

  auto encode = [&](pii a) -> int {
    if (a == dest) return R * C;
    auto [x, y] = a;
    return x * C + y;
  };

  auto decode = [&](int i) -> pii {
    if (i == R * C) return dest;
    return {i / C, i % C};
  };

  vc costs(R * C + 1, vc<pii>(R * C + 1, {INF, INF}));
  vc<vc<pii>> by_cost(2 * R * C + 1);
  auto push = [&](pii a1, pii a2, pii cost) -> void {
    if (a1 == a2 and a1 != dest) return;
    int i1 = encode(a1), i2 = encode(a2);
    if (cost >= costs[i1][i2]) return;
    costs[i1][i2] = cost;
    by_cost[cost.fs].eb(i1, i2);
  };
  push({R1, C1}, {R2, C2}, {0, 0});
  rep(cost, 0, 2 * R * C + 1) {
    for (auto [i1, i2] : by_cost[cost]) {
      auto [c1, c2] = costs[i1][i2];
      if (c1 != cost) continue;

      if (i1 == R * C and i2 == R * C) {
        cout << c1 << ' ' << c2 << '\n';
        exit(0);
      }

      pii a1 = decode(i1), a2 = decode(i2);
      rep(d, 0, 4) {
        auto [b1, dc21] = move(a1, d);
        auto [b2, dc22] = move(a2, (d + dd) % 4);
        push(b1, b2, {c1 + 1, c2 + dc21 + dc22});
      }
    }
    by_cost[cost].clear();
  }
}
