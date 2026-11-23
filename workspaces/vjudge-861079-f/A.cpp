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

const int LOGA = 30;
const int INF = 1e18;

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

    vi X(N);
    for (auto &e : X) cin >> e;

    auto grundy = [&](int a, int x) -> int {
      x &= (1ll << (__lg(a) + 1)) - 1;
      if (x > a) {
        vc dp(LOGA + 1, vc(LOGA + 1, vc(3, vc(3, vc<char>(2, false)))));
        dp[LOGA][0][1][1][0] = true;
        for (int i = LOGA - 1; i >= 0; i--) {
          int d1 = a >> i & 1, d2 = x >> i & 1;
          rep(j, 0, LOGA - i) {
            rep(k, 0, 3) {
              rep(l, 0, 3) {
                rep(m, 0, 2) {
                  rep(n, 0, d2 + 1) {
                    dp[i][j + n][k == 1 ? n < d1   ? 0
                                          : n > d1 ? 2
                                                   : 1
                                        : k][l == 1 ? d2 - n < d1   ? 0
                                                      : d2 - n > d1 ? 2
                                                                    : 1
                                                    : l]
                      [m == 0 ? d2 - n > 0 ? 1 : 0 : m] |=
                        dp[i + 1][j][k][l][m];
                  }
                }
              }
            }
          }
        }
        int mex = 0;
        rep(i, 0, LOGA + 1) {
          if (dp[0][i][2][0][1] or dp[0][i][2][1][1]) {
            chmax(mex, __builtin_popcountll(x) - i);
          }
        }
        while (dp[0][mex][0][0][1] or dp[0][mex][0][1][1] or
               dp[0][mex][1][0][1] or dp[0][mex][1][1][1]) {
          mex++;
        }
        return mex;
      } else {
        return __builtin_popcountll(x);
      }
    };
    rep(i, 0, N) { cerr << grundy(A[i], X[i]) << ' '; }
    cerr << '\n';
    auto brute = [&](int a, int x) -> int {
      vi dp(x + 1);
      rep(j, 0, x + 1) {
        set<int> seen;
        rep(k, 1, min(a, j) + 1) {
          if ((j & k) != k) continue;
          seen.insert(dp[j - k]);
        }
        int mex = 0;
        while (seen.contains(mex)) {
          mex++;
        }
        dp[j] = mex;
      }
      return dp[x];
    };
    // rep(i, 0, N) { cerr << brute(A[i], X[i]) << ' '; }
    // cerr << '\n';
    cerr << brute(64, 64) << ' ' << brute(64, 66) << ' ' << brute(64, 68) << ' '
         << brute(64, 70) << ' ' << brute(64, 78) << '\n';
    int nim = 0;
    rep(i, 0, N) { nim ^= grundy(A[i], X[i]); }
    cout << (nim == 0 ? "Bob" : "Alice") << '\n';
  }
}
