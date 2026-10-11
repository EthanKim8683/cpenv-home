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

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  map<int, int> counts;
  for (auto e : A) {
    counts[e] += 1;
  }

  int ans = 0;
  for (auto [e, count] : counts) {
    int sum = 0;
    rep(i, 0, 5 + 1) {
      if (!counts.contains(e + i)) continue;
      sum += counts[e + i];
    }
    chmax(ans, sum);
  }
  cout << ans << '\n';
}
