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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // like coming up with the answer is 10% effort, but writing impl is the
  // remaining 90% so if I can test the hypothesis & if its wrong i won't risk
  // writing impl
  // i can explain idea to u then
  // what plan do u have after class? no plan
  // library??

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi A(M);
    for (auto &e : A) cin >> e;

    auto build = [&](int x) -> vc<string> {
      vc rv(N, string(M, '.'));
      vc dp(M + 1, vi(N));
      fill(all(dp[0]), 0);
      rep(i, 0, M) {
        dp[i + 1] = dp[i];

        int used = 0;
        rep(j, 0, N) {
          if (used == A[i]) break;
          int c = j - 1 >= 0 ? dp[i][j - 1] : 0;
          if (c + 1 == dp[i][j]) {
            rv[j][i] = '#';
            used++;
          }
        }

        int cmax = *max_element(all(dp[i]));
        vi ge(cmax + 2, 0);
        rep(j, 0, N) { ge[dp[i][j]]++; }
        for (int j = cmax + 1; j - 1 >= 0; j--) {
          ge[j - 1] += ge[j];
        }
        for (int j = N - 1; j >= 0; j--) {
          if (used == A[i]) break;
          if (rv[j][i] == '#') continue;
          int c = j - 1 >= 0 ? dp[i][j - 1] : 0;
          if (ge[c + 1] < x - (c + 1) + 1) {
            dp[i + 1][j] = c + 1;
            ge[c + 1]++;
            rv[j][i] = '#';
            used++;
          }
        }

        vc<vi> by_c(cmax + 1);
        for (int j = N - 1; j >= 0; j--) {
          if (rv[j][i] == '#') continue;
          int c = j - 1 >= 0 ? dp[i][j - 1] : 0;
          by_c[c].pb(j);
        }
        rep(c, 0, cmax + 1) {
          for (auto j : by_c[c]) {
            if (used == A[i]) break;
            dp[i + 1][j] = c + 1;
            rv[j][i] = '#';
            used++;
          }
        }
      }
      if (*max_element(all(dp[M])) > x) return {};
      return rv;
    };
    int l = 0, r = min(N, M);
    while (l < r) {
      int m = l + (r - l) / 2;
      !build(m).empty() ? r = m : l = m + 1;
    }
    cout << l << '\n';
    for (auto e : build(l)) {
      cout << e << '\n';
    }
  }
}
