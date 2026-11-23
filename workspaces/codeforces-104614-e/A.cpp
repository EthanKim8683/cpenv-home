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

  // everything is a binary tree
  // ...except when they're not
  // ...but they're always on the exterior and they're simple because it's just
  // a straight path out
  //
  // find distance to root of tree
  // or find distance to anti-root? (root, then follow straight path out)
  // once you get to anti-root, there might still be a root awaiting you
  // nice, so it's lca
  //
  // let's make it so that all siblings lie on a straight line. this makes
  // distance calculations after lca easy
  //
  // we can handle coordinates outside the maze like this as well. their parents
  // are where they hit the maze, and the parents of that are the corners
  //
  // now let's figure out the encode function
  // recursively find quadrants. hmm sometimes we skip parents
  //
  // let's rephrase this: encode function says how to get out of your quadrant
  // over and over again
  // this gives us either lca if the final destination is maze root or casework
  // if it's not
  // how to get out is based on what hallway you're in. if you're in the top
  // hallway, you just go up. if you're on the horizontal hallways, go to
  // middle, then go out. if you're in the bottom hallway, go down
  //
  // perfect. now let's figure out rotations
  // when we go inside a quadrant, we want to rotate the world so it looks like
  // the quadrant is right side up. we also want to align it so that the bottom
  // left is at (0, 0)
  // going back out just involves undoing this transformation
  // i think a good order is doing the translation first, then doing the
  // rotation

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    int X1, Y1, X2, Y2;
    cin >> X1 >> Y1 >> X2 >> Y2;

    int K = (1ll << N) - 1;

    auto dfs = [&](auto self, int k, int x, int y) -> vc<pii> {
      int m = (k - 1) / 2;
      vc<pii> rv;
      if (y > m) {
        if (x < m) {
          rv = self(self, m, x, y - (m + 1));
          for (auto &[x2, y2] : rv) {
            tie(x2, y2) = pair{x2, y2 + (m + 1)};
          }
        } else if (x > m) {
          rv = self(self, m, x - (m + 1), y - (m + 1));
          for (auto &[x2, y2] : rv) {
            tie(x2, y2) = pair{x2 + (m + 1), y2 + (m + 1)};
          }
        } else {
          rv = {{x, y}};
        }
      } else if (y < m) {
        if (x < m) {
          rv = self(self, m, m - 1 - y, x);
          for (auto &[x2, y2] : rv) {
            tie(x2, y2) = pair{y2, m - 1 - x2};
          }
        } else if (x > m) {
          rv = self(self, m, y, k - 1 - x);
          for (auto &[x2, y2] : rv) {
            tie(x2, y2) = pair{k - 1 - y2, x2};
          }
        } else {
          rv = {{x, y}};
        }
      } else {
        rv = {{x, y}};
      }

      auto [x2, y2] = rv.back();
      if (y2 == m) {
        rv.eb(m, m);
        rv.eb(m, -1);
      } else if (x2 == m) {
        if (y2 > m) {
          rv.eb(m, k);
        } else {
          rv.eb(m, -1);
        }
      }
      return rv;
    };

    auto is_inside = [&](int x, int y) -> bool {
      return 0 <= x and x < K and 0 <= y and y < K;
    };

    auto encode = [&](int x, int y) -> vc<pii> {
      if (!is_inside(x, y)) return {{x, y}};
      auto rv = dfs(dfs, K, x, y);
      rv.erase(unique(all(rv)), rv.end());
      reverse(all(rv));
      return rv;
    };

    auto dist = [&](pii a, pii b) -> int {
      auto [x1, y1] = a;
      auto [x2, y2] = b;
      return abs(x2 - x1) + abs(y2 - y1);
    };

    auto path1 = encode(X1, Y1), path2 = encode(X2, Y2);

    int k = 0;
    for (; k < min(sz(path1), sz(path2)) - 1; k++) {
      if (path1[k] != path2[k]) break;
    }

    auto third = [&](int x) -> int {
      if (x < 0) return -1;
      if (x < K) return 0;
      return 1;
    };

    int sum = INF;
    pii a = path1[k], b = path2[k];
    if (third(a.fs) * third(b.fs) == -1 and third(a.sd) == 0 and
        third(b.sd) == 0) {
      pii c = {0, K}, d = {0, -1};
      chmin(sum, dist(a, c) + dist(c, b));
      chmin(sum, dist(a, d) + dist(d, b));
    } else if (third(a.sd) * third(b.sd) == -1 and third(a.fs) == 0 and
               third(b.fs) == 0) {
      pii c = {K, 0}, d = {-1, 0};
      chmin(sum, dist(a, c) + dist(c, b));
      chmin(sum, dist(a, d) + dist(d, b));
    } else {
      sum = dist(a, b);
    }
    rep(i, k, sz(path1) - 1) { sum += dist(path1[i], path1[i + 1]); }
    rep(i, k, sz(path2) - 1) { sum += dist(path2[i], path2[i + 1]); }
    cout << sum << '\n';
  }
}
