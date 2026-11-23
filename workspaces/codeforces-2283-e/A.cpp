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

const int MAXN = 5000;
const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // split into substrings
  //
  // put substrings in sets. start with 01 substrings, then add the 0 and 1
  // substrings
  //
  // remaining substrings can be put together without changing cost
  //
  // if there are any 01 substrings, make a set of everything
  //
  // ah. not really. the condition must hold for all pairs. it's not transitive
  //
  // we can only have sets like 010, 101, 01, 10, 0000... and 1111...
  //
  // you don't want to choose 01, 10 unless you have to. prefer 010 and 101
  //
  // ah i'm stupid i see now
  //
  // 01010101010 -> can be partitioned nicely
  //
  // it's just alternating shit

  vc dp(MAXN + 1, vi(MAXN + 1, 0));
  dp[0][0] = 1;
  rep(i, 0, MAXN) {
    rep(j, 0, i + 1) {
      (dp[i + 1][j + 1] += dp[i][j]) %= MOD;
      (dp[i + 1][j] += dp[i][j] * j) %= MOD;
    }
  }

  vi sums(MAXN + 1, 0);
  rep(i, 0, MAXN + 1) {
    rep(j, 0, i + 1) { (sums[i] += dp[i][j]) %= MOD; }
  }

  vi dp2(MAXN + 1, 0);
  dp2[0] = 1;
  rep(i, 0, MAXN) {
    if (i + 2 <= MAXN) {
      (dp2[i + 2] += dp2[i]) %= MOD;
    }
    if (i + 3 <= MAXN) {
      (dp2[i + 3] += dp2[i]) %= MOD;
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    vi lefts(N);
    iota(all(lefts), 0);
    for (int i = 0; i < N - 1; i++) {
      if (S[i] != S[i + 1]) {
        lefts[i + 1] = lefts[i];
      }
    }
    vc<pii> groups;
    for (int i = 0, j; i < N; i = j) {
      for (j = i; j < N and lefts[i] == lefts[j]; j++);
      groups.eb(i, j);
    }
    int ans = 1;
    vi counts(2, 0);
    for (auto [i, j] : groups) {
      if (lefts[i] == lefts[j - 1] and j - i >= 2) {
        (ans *= dp2[j - i]) %= MOD;
      } else {
        rep(k, i, j) { counts[S[k] - '0']++; }
      }
    }
    (ans *= sums[counts[0]]) %= MOD;
    (ans *= sums[counts[1]]) %= MOD;
    cout << 2 * N - counts[0] - counts[1] << ' ' << ans << '\n';
  }
}
