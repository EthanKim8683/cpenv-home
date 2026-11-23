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

const double PI = acosl(-1.L);

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  auto intersect = [&](double r1, double r2, double d) -> pair<double, double> {
    double cos = (r1 * r1 + d * d - r2 * r2) / (2 * r1 * d);
    if (!(-1 <= cos and cos <= 1)) return {-1, -1};
    double theta = acosl(cos);
    return {r1 * cosl(theta), r1 * sinl(theta)};
  };

  auto arc = [&](double r, double theta) -> double {
    return r * r * theta / 2;
  };

  auto sec1 = [&](double r, double theta) -> double {
    return r * r * sinl(theta) / 2;
  };

  auto sec2 = [&](double r, double theta) -> double {
    return arc(r, theta) - sec1(r, theta);
  };

  auto overlap1 = [&](double r1, double r2) -> double {
    auto [d1, d2] = intersect(r1, r2, r1);
    if (d1 < 0) return 0;
    double theta1 = asinl(d2 / r2), theta2 = asinl(d2 / r1);
    return arc(r2, 2 * theta1) + 2 * sec2(r1, theta2);
  };

  auto overlap2 = [&](double r1, double r2, double theta) -> double {
    theta = fmodl(abs(theta), 2 * PI);
    theta = min(theta, 2 * PI - theta);
    if (theta == 0) return overlap1(r1, r2);
    double d1 = r1 * sinl(theta / 2), d2 = r1 * cosl(theta / 2);
    auto [d3, d4] = intersect(r2, r2, 2 * d1);
    if (d3 < 0) return 0;
    if (d2 + d4 < r1) {
      double phi = asinl(d4 / r2);
      return 2 * sec2(r2, 2 * phi);
    } else {
      auto [d5, d6] = intersect(r1, r2, r1);
      double d7 = d5 * cosl(theta / 2) + d6 * sinl(theta / 2),
             d8 = d6 * cosl(theta / 2) - d5 * sinl(theta / 2),
             phi1 = asinl(d8 / r1),
             phi2 = acosl(d1 / r2) + atanl((d7 - d2) / (d1 + d8)),
             d9 = d7 - (d2 - d4);
      return sec2(r1, 2 * phi1) + 2 * sec2(r2, phi2) + d8 * d9;
    }
  };

  double R;
  int N, K;
  double C;
  cin >> R >> N >> K >> C;

  vc<double> A(N);
  for (auto &e : A) cin >> e;

  double overlap = overlap1(R, C);
  vc overlaps(N, vc<double>(N));
  rep(i, 0, N) {
    rep(j, i, N) { overlaps[i][j] = overlap2(R, C, A[i] - A[j]); }
  }

  vc dp(N + 1, vc(N + 1, vc<double>(K + 1, 0)));
  rep(i, 0, N) {
    chmax(dp[i][i][1], overlap);
    rep(j, 0, i) {
      rep(k, j, i) {
        rep(l, 0, min(k - j + 1, K - 1) + 1) {
          chmax(dp[j][i][l + 1], dp[j][k][l] + overlap - overlaps[k][i]);
        }
      }
    }
  }
  double ans = 0;
  rep(i, 0, N) {
    rep(j, i, N) { chmax(ans, dp[i][j][K] - (K >= 3 ? overlaps[i][j] : 0)); }
  }
  cout << setprecision(10) << fixed << ans << '\n';
}
