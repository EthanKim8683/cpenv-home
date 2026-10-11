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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  string t;
  cin >> t;

  auto w = [&](vc<string> grid) -> int {
    int rv = 0;
    for (auto e : grid) {
      rv += count(all(e), '#');
    }
    return rv;
  };

  auto normalize = [&](vc<string> &grid) -> void {
    int n = sz(grid);
    if (2 * w(grid) > n * n) {
      for (auto &r : grid) {
        for (auto &e : r) {
          if (e == '#') {
            e = '.';
          } else {
            e = '#';
          }
        }
      }
    }
  };

  auto sums = [&](vc<string> grid, int mod) -> pii {
    int n = sz(grid), rsum = 0, csum = 0;
    rep(i, 0, n) {
      rep(j, 0, n) {
        if (grid[i][j] == '#') {
          (rsum += i) %= mod;
          (csum += j) %= mod;
        }
      }
    }
    return {rsum, csum};
  };

  // auto mod_pow = [&](int x, int y, int mod) -> int {
  //   int rv = 1;
  //   for (x %= mod; y; y >>= 1, (x *= x) %= mod) {
  //     if (y & 1) {
  //       (rv *= x) %= mod;
  //     }
  //   }
  //   return rv;
  // };

  // auto mod_inv = [&](int x, int mod) -> int {
  //   return mod_pow(x, mod - 2, mod);
  // };

  auto gcd = [&](int a, int b, int &x, int &y) -> int {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
      int q = a1 / b1;
      tie(x, x1) = make_tuple(x1, x - q * x1);
      tie(y, y1) = make_tuple(y1, y - q * y1);
      tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
  };

  auto mod_inv = [&](int a, int m) -> int {
    int x, y;
    int g = gcd(a, m, x, y);
    x = (x % m + m) % m;
    return x;
  };

  if (t == "first") {
    int T;
    cin >> T;

    while (T--) {
      int N;
      cin >> N;

      vc<string> grid(N);
      for (auto &e : grid) cin >> e;
      normalize(grid);

      int R, C;
      cin >> R >> C;
      R--, C--;

      int W = w(grid);

      auto [rsum, csum] = sums(grid, N);
      int rd = (R * W % N + N - rsum) % N, cd = (C * W % N + N - csum) % N;

      int r1 = -1, c1, r2, c2;
      if (rd == 0 and cd == 0) {
        tie(r1, c1, r2, c2) = tuple{0, 0, 0, 0};
      } else {
        rep(i, 0, N) {
          rep(j, 0, N) {
            if (grid[i][j] == '#' and grid[(i + rd) % N][(j + cd) % N] == '.') {
              tie(r1, c1, r2, c2) = tuple{i, j, (i + rd) % N, (j + cd) % N};
            }
          }
        }
      }
      assert(r1 != -1);

      cout << r1 + 1 << ' ' << c1 + 1 << ' ' << r2 + 1 << ' ' << c2 + 1 << '\n';

      swap(grid[r1][c1], grid[r2][c2]);
      auto [rsum2, csum2] = sums(grid, N);
      assert(rsum2 == R * W % N);
      assert(csum2 == C * W % N);
    }
  } else {
    int T;
    cin >> T;

    while (T--) {
      int N;
      cin >> N;

      vc<string> grid(N);
      for (auto &e : grid) cin >> e;
      normalize(grid);

      int W = w(grid);

      int inv_w = mod_inv(W, N);
      auto [rsum, csum] = sums(grid, N);
      cout << rsum * inv_w % N + 1 << ' ' << csum * inv_w % N + 1 << '\n';
    }
  }
}
