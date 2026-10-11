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

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi B(M);
    for (auto &e : B) cin >> e;

    set<int> unseen;
    rep(i, 1, N + 1) { unseen.insert(i); }
    vi dp, lis(M, -INF);
    for (int i = M - 1; i >= 0; i--) {
      if (unseen.contains(B[i])) {
        unseen.erase(B[i]);
      }
      if (unseen.begin() != unseen.lower_bound(B[i])) continue;
      auto it = lower_bound(all(dp), B[i]);
      lis[i] = it - dp.begin() + 1;
      if (it == dp.end()) {
        dp.pb(B[i]);
      } else {
        *it = B[i];
      }
    }
    rep(i, 1, N + 1) { unseen.insert(i); }
    dp.clear();
    vi lds(M, -INF);
    for (int i = M - 1; i >= 0; i--) {
      if (unseen.contains(B[i])) {
        unseen.erase(B[i]);
      }
      if (unseen.upper_bound(B[i]) != unseen.end()) continue;
      auto it = lower_bound(all(dp), B[i], greater<int>());
      lds[i] = it - dp.begin() + 1;
      if (it == dp.end()) {
        dp.pb(B[i]);
      } else {
        *it = B[i];
      }
    }
    int ans = INF;
    rep(i, 0, M) { chmin(ans, N - (lis[i] + lds[i] - 1)); }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
