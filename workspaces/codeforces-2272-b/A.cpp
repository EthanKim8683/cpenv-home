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
    int N;
    cin >> N;

    vc<string> grid(2);
    for (auto &e : grid) cin >> e;

    vi counts(2);
    rep(i, 0, 2) { counts[i] = count(all(grid[i]), 'f'); }

    vi wastes(2, 0);
    rep(i, 0, 2) {
      rep(j, 0, N - 1) {
        if (grid[i][j] == 'f' and grid[i][j + 1] == 'f') {
          wastes[i]++;
          j++;
        }
      }
    }

    int ans;
    if (counts[0] > counts[1]) {
      if (counts[0] % 2 != counts[1] % 2) {
        ans = max(counts[0] - counts[1] - 2 * wastes[0], 1ll);
      } else {
        ans = max(counts[0] - counts[1] - 2 * wastes[0], 0ll);
      }
    } else if (counts[1] > counts[0]) {
      if (counts[0] % 2 != counts[1] % 2) {
        ans = max(counts[1] - counts[0] - 2 * wastes[1], 1ll);
      } else {
        ans = max(counts[1] - counts[0] - 2 * wastes[1], 0ll);
      }
    } else {
      ans = 0;
    }
    cout << ans << '\n';
  }
}
