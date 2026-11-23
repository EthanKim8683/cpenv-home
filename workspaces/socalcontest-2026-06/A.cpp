#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
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

  // at each point, do i keep going or add what i already have
  //
  // we keep going if ev from this point is higher than what i can already get
  //
  // in the end, we calculate the final ev with the prior ev and compare
  //
  // if it's below, our prior ev was wrong and we decrease it
  //
  // our final ev can be calculated from the root

  int N;
  cin >> N;

  vi X(1 << N);
  rep(i, 1, 1 << N) { cin >> X[i]; }

  auto check = [&](double x) -> bool {
    vi sums(1 << N);
    sums[1] = 0;
    rep(i, 1, (1 << N) / 2) {
      sums[i << 1] = sums[i] + X[i << 1];
      sums[i << 1 | 1] = sums[i] + X[i << 1 | 1];
    }

    vc<double> dp(1 << N);
    rep(i, (1 << N) / 2, 1 << N) { dp[i] = sums[i] + x; }
    for (int i = (1 << N) / 2 - 1; i >= 1; i--) {
      // p(both) = no bit in their or is set
      // p(left) = no bit in left is set - p(both)
      // p(right) = no bit in right is set - p(both)

      int l = X[i << 1], r = X[i << 1 | 1], pc1 = __builtin_popcountll(l | r),
          pc2 = __builtin_popcountll(l), pc3 = __builtin_popcountll(r);
      double p1 = (double) (1ll << (N - pc1)) / (1ll << N),
             p2 = (double) (1ll << (N - pc2)) / (1ll << N) - p1,
             p3 = (double) (1ll << (N - pc3)) / (1ll << N) - p1,
             p4 = 1 - p1 - p2 - p3;
      dp[i] = max(p1 * max(dp[i << 1], dp[i << 1 | 1]) + p2 * dp[i << 1] +
                      p3 * dp[i << 1 | 1],
                  (double) sums[i]);
    }
    return dp[1] < x;
  };
  double l = 0, r = 1e18;
  rep(i, 0, 90) {
    double m = (l + r) / 2;
    check(m) ? r = m : l = m;
  }
  cout << setprecision(10) << fixed << l << '\n';
}
