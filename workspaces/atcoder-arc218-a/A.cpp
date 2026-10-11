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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, M;
  cin >> N >> M;

  vc A(N, vi(M));
  for (auto &r : A) {
    for (auto &e : r) {
      cin >> e;
      e--;
    }
    sort(all(r));
  }

  int ans = 0;
  vi idx(N, 0);
  rep(i, 0, N * M) {
    int dp0 = 1, dp1 = 0, z = 1;
    rep(j, 0, N) {
      int n = 0;
      for (; idx[j] < M; idx[j]++) {
        if (A[j][idx[j]] != i) break;
        n++;
      }
      tie(dp0, dp1) =
          make_pair((dp0 * M + dp1 * n) % MOD, (dp1 * M + dp0 * n) % MOD);
      (z *= M) %= MOD;
    }
    (ans += dp1 - dp0 + z) %= MOD;
  }
  (ans += MOD) %= MOD;
  cout << ans << '\n';
}
