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

const int MAXX = 500;
const int MAXY = 500;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

struct slow_insert_line_container {
  int n;
  vi y;
  slow_insert_line_container(int n) : n(n), y(n, INF) {}
  void insert(pii line) {
    auto [m, b] = line;
    rep(x, 0, n) { chmin(y[x], m * x + b); }
  }
  int get(int x) { return y[x]; }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<tuple<int, int, int>> monsters(N);
    for (auto &[x, y, z] : monsters) {
      cin >> x >> y >> z;
    }

    vi ps(N + 1);
    ps[0] = 0;
    rep(i, 0, N) {
      auto [x, y, z] = monsters[i];
      ps[i + 1] = ps[i] + z;
    }

    int ans = ps[N] - ps[0];
    vc dp(MAXX, slow_insert_line_container(MAXY));
    dp[0].insert({-2 * 0, 0 + 0 * 0 - ps[0]});
    rep(i, 0, N) {
      auto [x, y, z] = monsters[i];
      int best = INF;
      rep(x2, 0, MAXX) {
        chmin(best, dp[x2].get(y) + y * y + (x - x2) * (x - x2) + ps[i]);
      }
      dp[x].insert({-2 * y, best + y * y - ps[i + 1]});
      chmin(ans, best + ps[N] - ps[i + 1]);
    }
    cout << ans << '\n';
  }
}
