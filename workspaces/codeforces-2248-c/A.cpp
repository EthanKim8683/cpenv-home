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

    vi A(2 * N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vc<vi> by_left(2 * N);
    vi left(N, -1);
    rep(i, 0, 2 * N) {
      if (left[A[i]] == -1) {
        left[A[i]] = i;
      } else {
        by_left[left[A[i]]].pb(i);
      }
    }

    vi dp(2 * N + 1, 0);
    rep(i, 0, 2 * N) {
      for (auto e : by_left[i]) {
        chmax(dp[e + 1], dp[i] + (e - i + 1) * (e - i + 1));
      }
      chmax(dp[i + 1], dp[i] + 1);
    }
    cout << dp[2 * N] << '\n';
  }
}
