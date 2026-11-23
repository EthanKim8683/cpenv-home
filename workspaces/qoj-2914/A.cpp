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

  // greedy. order solvable problems by time to solve, then try to solve them in
  // this order
  //
  // p problems before, s problems after, d time taken prior

  int N, K, T;
  cin >> N >> K >> T;

  vc<pair<double, int>> problems(N);
  for (auto &[p, s] : problems) {
    cin >> p >> s;
  }

  vi order(N);
  iota(all(order), 0);
  sort(all(order),
       [&](int a, int b) -> bool { return problems[a].sd < problems[b].sd; });

  vc binom(N + 1, vc<double>(N + 1));
  rep(i, 0, N + 1) {
    binom[i][0] = 1;
    binom[i][i] = 1;
    rep(j, 1, i) { binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j]; }
  }

  vc dp(N + 1, vc(N + 1, vc<double>(T + 1, 0)));
  dp[0][0][0] = 1;
  rep(i, 0, N) {
    rep(j, 0, i + 1) {
      rep(k, 0, T + 1) {
        auto [p, s] = problems[order[i]];
        dp[i + 1][j + 1][k] += dp[i][j][k] * (1 - p);
        dp[i + 1][j + 1][min(k + s, T)] += dp[i][j][k] * p;
        dp[i + 1][j][k] += dp[i][j][k];
      }
    }
  }

  vc<double> ans(N, 0);
  rep(i, 0, N) {
    rep(j, 0, min(i, K - 1) + 1) {
      rep(k, 0, T + 1) {
        auto [p, s] = problems[order[i]];
        if (k + s <= T) {
          ans[order[i]] += p * dp[i][j][k] * binom[N - (i + 1)][K - 1 - j];
        }
      }
    }
  }
  for (auto &e : ans) {
    e /= binom[N - 1][K - 1];
  }
  cout << setprecision(10) << fixed;
  for (auto e : ans) {
    cout << e << '\n';
  }
}
