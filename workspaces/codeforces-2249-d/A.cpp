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

    if (__builtin_popcountll(N) > 1) {
      cout << "-1\n";
      continue;
    }

    if (X == 0) {
      rep(i, 0, N) {
        rep(j, 0, N) { cout << (i ^ j) << ' '; }
        cout << '\n';
      }
      continue;
    }

    if (N == 2) {
      cout << "-1\n";
      continue;
    }

    set<int> seen;
    seen.insert(0);
    seen.insert(X);
    vi indeps;
    while (true) {
      int x = -1;
      rep(j, 0, N) {
        if (seen.contains(j)) continue;
        x = j;
        break;
      }
      if (x == -1) break;

      indeps.pb(x);
      for (auto e : seen) {
        seen.insert(e ^ x);
      }
    }

    auto dfs = [&](auto self, int n) -> vc<vi> {
      if (n == 2) {
        int y = indeps[0];
        return {{0, y}, {y, X}};
      }

      int y;
      if (n == 4) {
        y = X;
      } else {
        y = indeps[__lg(n) - 2];
      }
      auto sub = self(self, n / 2);
      vc rv(n, vi(n));
      rep(i, 0, 2) {
        rep(j, 0, 2) {
          rep(k, 0, n / 2) {
            rep(l, 0, n / 2) {
              rv[n / 2 * i + k][n / 2 * j + l] = sub[k][l] ^ (i * y) ^ (j * y);
            }
          }
        }
      }
      return rv;
    };
    auto ans = dfs(dfs, N);
    for (auto r : ans) {
      for (auto e : r) {
        cout << e << ' ';
      }
      cout << '\n';
    }

    // rep(i, 0, N - 1) {
    //   rep(j, 0, N - 1) {
    //     cerr << (ans[i][j] ^ ans[i + 1][j] ^ ans[i][j + 1] ^ ans[i + 1][j +
    //     1])
    //          << ' ';
    //   }
    //   cerr << '\n';
    // }
  }
}
