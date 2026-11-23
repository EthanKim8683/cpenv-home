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

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<vi> by_parity(2);
    for (auto e : A) {
      by_parity[e % 2].pb(e);
    }

    vi A2;
    rep(i, 0, 2 * N) {
      if (i / 2 < sz(by_parity[i % 2])) {
        A2.pb(by_parity[i % 2][i / 2]);
      }
    }
    int ans = 0;
    rep(i, 0, N - 1) { ans += (A2[i] + A2[i + 1]) / 2; }
    cout << ans << '\n';
  }
}
