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
const int MOD = 1e9 + 7;

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

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps(N + 1, 0);
    vc<pii> ranges;
    rep(k, 1, N + 1) {
      int m = A[k - 1];
      int l = min(m * k, N), r = min((m + 1) * k, N);
      ps[l] += 1;
      ps[r] -= 1;
      rep(i, 0, m) { ranges.eb(i * k, min((i + 1) * k, N)); }
    }
    rep(i, 0, N) { ps[i + 1] += ps[i]; }

    sort(all(ranges), [&](pii a, pii b) -> bool {
      auto key = [&](pii x) -> pii {
        auto [l, r] = x;
        return {r, -l};
      };
      return key(a) < key(b);
    });
    vc<pii> ranges2;
    int lmax = -INF;
    for (auto [l, r] : ranges) {
      if (l > lmax) {
        ranges2.eb(l, r);
        lmax = l;
      }
    }
    sort(all(ranges2));
    int M = sz(ranges2);

    vi dp(M + 1, 0);
    dp[0] = 1;
    int sum = 0, p1 = 0, p2 = 0;
    rep(i, 0, N) {
      for (; p1 < M; p1++) {
        if (i < ranges2[p1].sd) break;
        (sum -= dp[p1]) %= MOD;
      }
      for (; p2 < M; p2++) {
        if (i < ranges2[p2].fs) break;
        (sum += dp[p2]) %= MOD;
      }
      if (ps[i] == 0) {
        (dp[p2] *= 2) %= MOD;
        (dp[p2] += sum) %= MOD;
      }
    }
    cout << (dp[M] + MOD) % MOD << '\n';
  }
}
