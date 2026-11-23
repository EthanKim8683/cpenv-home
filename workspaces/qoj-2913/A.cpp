#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

const double INF = 1.L / 0;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<double> P(N);
  for (auto &e : P) cin >> e;

  vi S(N);
  for (auto &e : S) cin >> e;

  auto rref = [&](vc<vc<double>> A) -> vc<vc<double>> {
    // int i = 0;
    // rep(j, 0, sz(A[0])) {
    //     int l = -1;
    //     rep(k, i, sz(A)) {
    //         if (abs(A[k][j] - 0) > EPS) {
    //             l = k;
    //         }
    //     }
    //     if (l == -1) continue;
    //     swap(A[i], A[l]);
    //
    //     double x = A[i][j];
    //     for (auto &e : A[i]) {
    //         e /= x;
    //     }
    //
    //     rep(k, 0, sz(A)) {
    //         if (k == i) continue;
    //         double x = -A[k][j];
    //         if (abs(x - 0) < EPS) continue;
    //         rep(m, 0, sz(A[k])) {
    //             A[k][m] += x * A[i][m];
    //         }
    //     }
    //
    //     i++;
    // }
    // return A;

    rep(i, 0, sz(A)) {
      double x = A[i][1];
      for (auto &e : A[i]) {
        e /= x;
      }
      if (i + 1 < sz(A)) {
        A[i + 1][1] -= A[i + 1][0] * A[i][2];
      }
    }
    for (int i = sz(A) - 1; i - 1 >= 0; i--) {
      A[i - 1][3] -= A[i - 1][2] * A[i][3];
    }
    return A;
  };

  vc probs(N, vc<vc<double>>(N));
  rep(i, 0, N) {
    rep(j, 0, N) {
      vc A(2 * S[j] + 1, vc<double>(4, 0));
      A[0][1] = 1;
      A[0][3] = 0;
      A[2 * S[j]][1] = 1;
      A[2 * S[j]][3] = 1;
      rep(k, 1, 2 * S[j]) {
        A[k][0] = 1 - P[i];
        A[k][1] = -1;
        A[k][2] = P[i];
        A[k][3] = 0;
      }
      A = rref(A);
      rep(k, 0, 2 * S[j] + 1) { probs[i][j].pb(A[k][3]); }
    }
  }

  vc<double> dp(1 << N, 0);
  dp[0] = 1;
  rep(i, 0, 1 << N) {
    int j = __builtin_popcount(i);
    rep(k, 0, N) {
      if (i >> k & 1) continue;
      int s1 = j - 1 >= 0 ? S[j - 1] : 0, s2 = S[j];
      chmax(dp[i | 1 << k],
            dp[i] * probs[k][j][s2 + s1] + (1 - dp[i]) * probs[k][j][s2 - s1]);
    }
  }
  cout << setprecision(10) << fixed << dp[(1 << N) - 1] << '\n';
}
