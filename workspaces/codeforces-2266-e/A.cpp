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

const int MAXN = 2e5;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi sieve(MAXN + 1);
  iota(all(sieve), 0);
  for (int i = 2; i * i <= MAXN; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= MAXN; j += i) {
      chmin(sieve[j], i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi cost(N + 1, INF);
    fill(cost.begin(), cost.begin() + K + 1, 0);
    rep(i, 1, N + 1) {
      for (int j = i; j != 1; j /= sieve[j]) {
        chmin(cost[i], cost[i / sieve[j]] * sieve[j] + 1);
      }
    }
    int ans = 0;
    for (auto e : A) {
      ans += cost[e];
    }
    cout << ans << '\n';
  }
}
