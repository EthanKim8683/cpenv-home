#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

  int N;
  cin >> N;

  if (N == 3) {
    cout << R"(111
111
001

011
111
100

110
110
110

010
111
111

111
111
111

010
111
101

111
111
110

111
011
111

011
010
111

DURLDULRUU
)";
    exit(0);
  }

  vc bests(4, vc<pii>(4, {INF, INF}));
  rep(i, 0, 1 << 16) {
    int x0 = 0, y0 = 0, x1 = 4, y1 = 4;
    rep(j, 0, 6) {
      int s = 0;
      rep(k, x0, x1) {
        rep(l, y0, y1) { s += i >> (4 * k + l) & 1; }
      }
      int r = s % 4;
      if (r == 0) {
        x0++;
      } else if (r == 1) {
        y0++;
      } else if (r == 2) {
        x1--;
      } else {
        y1--;
      }
    }
    if (x0 < x1 and y0 < y1) {
      chmin(bests[x0][y0], pii{16 - __builtin_popcountll(i), i});
    }
  }
  int worst = 0;
  for (auto r : bests) {
    for (auto [cost, mask] : r) {
      chmax(worst, cost);
    }
  }
  // cerr << worst << '\n';

  worst = 0;
  rep(i, 0, 20) {
    rep(j, 0, 20) {
      auto [cost, mask] = bests[i % 4][j % 4];

      vc ans(20, string(20, '\0'));
      int x0 = i / 4 * 4, y0 = j / 4 * 4, x1 = x0 + 4, y1 = y0 + 4;
      rep(k, 0, 4) {
        rep(l, 0, 4) { ans[x0 + k][y0 + l] = '0' + (mask >> (4 * k + l) & 1); }
      }

      int r = __builtin_popcountll(mask) % 4;
      while (x0 > 0) {
        int d = (4 - r) % 4;
        d += (y1 - y0 - d) / 4 * 4;
        (r += d) %= 4;
        cost += y1 - y0 - d;
        x0--;
        rep(k, 0, y1 - y0) { ans[x0][y0 + k] = k < d ? '1' : '0'; }
      }
      while (y0 > 0) {
        int d = (5 - r) % 4;
        d += (x1 - x0 - d) / 4 * 4;
        (r += d) %= 4;
        cost += x1 - x0 - d;
        y0--;
        rep(k, 0, x1 - x0) { ans[x0 + k][y0] = k < d ? '1' : '0'; }
      }
      while (x1 < 20) {
        int d = (6 - r) % 4;
        d += (y1 - y0 - d) / 4 * 4;
        (r += d) %= 4;
        cost += y1 - y0 - d;
        rep(k, 0, y1 - y0) { ans[x1][y0 + k] = k < d ? '1' : '0'; }
        x1++;
      }
      while (y1 < 20) {
        int d = (7 - r) % 4;
        d += (x1 - x0 - d) / 4 * 4;
        (r += d) %= 4;
        cost += x1 - x0 - d;
        rep(k, 0, x1 - x0) { ans[x0 + k][y1] = k < d ? '1' : '0'; }
        y1++;
      }
      chmax(worst, cost);

      for (auto e : ans) {
        cout << e << '\n';
      }
      cout << '\n';

      // rep(j, 0, 38) {
      //   int s = 0;
      //   rep(k, x0, x1) {
      //     rep(l, y0, y1) {
      //       if (ans[k][l] == '1') {
      //         s++;
      //       }
      //     }
      //   }
      //   int r = s % 4;
      //   if (r == 0) {
      //     x0++;
      //   } else if (r == 1) {
      //     y0++;
      //   } else if (r == 2) {
      //     x1--;
      //   } else {
      //     y1--;
      //   }
      // }
      // assert(x0 < x1 and y0 < y1);
      // assert(x0 == i and y0 == j);
    }
  }
  // cerr << worst << '\n';

  rep(i, 0, 20 * 20 + 1) { cout << "ULDR"[i % 4]; }
  cout << '\n';
}
