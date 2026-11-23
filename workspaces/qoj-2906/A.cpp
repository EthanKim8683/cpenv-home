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

const int LOGA = 25;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // x belongs to a triple iff, among all minimal sets of islanders such that
  // excluding such a set results in zero triples, there exists a set that
  // contains x
  //
  // this bounds the problem to finding the size of the minimal set
  //
  //

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  vc<char> dp(1 << N, false);
  rep(i, 0, N) {
    rep(j, i + 1, N) {
      rep(k, j + 1, N) {
        if ((A[i] ^ A[j] ^ A[k]) == 0) {
          dp[1 << i | 1 << j | 1 << k] = true;
        }
      }
    }
  }
  rep(i, 0, 1 << N) {
    rep(j, 0, N) { dp[i | 1 << j] |= dp[i]; }
  }
  int ans = N;
  rep(i, 0, 1 << N) {
    if (!dp[i]) {
      chmin(ans, N - __builtin_popcount(i));
    }
  }
  cout << ans << '\n';
}
