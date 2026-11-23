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

  //

  int N, K;
  cin >> N >> K;

  vi A(N);
  for (auto &e : A) cin >> e;

  int ans = INF;
  rep(i, 0, 19) {
    vc<vi> sums(2e5 + 1);
    for (auto e : A) {
      int s = max(__lg(e) + 1 - i, 0ll);
      e >>= s;
      auto &costs = sums[e];
      costs.pb(s);
    }
    for (auto costs : sums) {
      sort(all(costs));
      if (sz(costs) < K) continue;
      int sum = 0;
      rep(i, 0, K) { sum += costs[i]; }
      chmin(ans, sum);
    }
  }
  cout << ans << '\n';
}
