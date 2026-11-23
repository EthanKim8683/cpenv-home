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
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi dp(N), ps(N + 1, 0);
    rep(i, 0, N) {
      dp[i] = (min(K, i) + ps[i] - ps[max(i - K, 0ll)]) % 2;
      ps[i + 1] = ps[i] + dp[i];
    }
    int ans = 0;
    rep(i, 0, N) { (ans += A[i] + A[i] * dp[i]) %= 2; }
    cout << (ans % 2 == 0 ? "Bob" : "Alice") << '\n';
  }
}
