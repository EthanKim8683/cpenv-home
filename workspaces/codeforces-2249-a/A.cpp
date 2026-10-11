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

    vc<tuple<int, int, int, int>> ranges(N);
    for (auto &[l, r, u, v] : ranges) {
      cin >> l >> r >> u >> v;
      l--, u--;
    }

    int ans = 0;
    rep(i, 0, N + 1) {
      int k = 0;
      rep(j, 0, N) {
        if (k == i) break;
        auto [l, r, u, v] = ranges[j];
        if ((l <= k and k < r) or (u <= i - 1 - k and i - 1 - k < v)) continue;
        k++;
      }
      if (k == i) {
        chmax(ans, i);
      }
    }
    cout << ans << '\n';
  }
}
