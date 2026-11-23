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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int H, W, Q;
  cin >> H >> W >> Q;

  vc<string> grid(H);
  for (auto &e : grid) cin >> e;

  vc grid2(W, string(H, '.'));
  rep(i, 0, W) {
    rep(j, 0, H) { grid2[i][j] = grid[j][i]; }
  }

  auto mask_from_col = [&](string s) -> int {
    int rv = 0;
    rep(i, 0, H) { rv |= (s[i] - '0') << i; }
    return rv;
  };

  auto costs_from_col = [&](string s) -> vi {
    int mask = mask_from_col(s);
    vi rv(1 << H);
    rep(i, 0, 1 << H) {
      int k = __builtin_popcount(mask ^ i);
      rv[i] = min(k, 1 + H - k);
    }
    return rv;
  };

  vi sums(1 << H, 0);
  auto contrib = [&](int i, int w) -> void {
    auto costs = costs_from_col(grid2[i]);
    rep(j, 0, 1 << H) { sums[j] += w * costs[j]; }
  };

  rep(i, 0, W) { contrib(i, 1); }

  int mask = 0;
  auto solve = [&]() -> int {
    int rv = INF;
    rep(i, 0, 1 << H) { chmin(rv, sums[i] + __builtin_popcount(i ^ mask)); }
    return rv;
  };

  cout << solve() << '\n';

  while (Q--) {
    char t;
    cin >> t;

    if (t == 'P') {
      int i, j;
      cin >> i >> j;
      i--, j--;

      contrib(j, -1);
      grid2[j][i] ^= 1;
      contrib(j, 1);
    } else if (t == 'R') {
      int i;
      cin >> i;
      i--;

      mask ^= 1 << i;
    } else {
      int j;
      cin >> j;
      j--;

      contrib(j, -1);
      for (auto &e : grid2[j]) {
        e ^= 1;
      }
      contrib(j, 1);
    }

    cout << solve() << '\n';
  }
}
