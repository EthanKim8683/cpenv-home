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

    vi H(N);
    for (auto &e : H) cin >> e;

    map<int, int, greater<>> counts;
    for (auto e : H) {
      counts[e] += 1;
    }

    int ans = 0;
    deque<int> H2;
    for (auto [x, count] : counts) {
      ans += min(count, 2ll);
      H2.push_front(x);
      rep(i, 1, count) { H2.pb(x); }
    }
    cout << ans << '\n';
    for (auto e : H2) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
