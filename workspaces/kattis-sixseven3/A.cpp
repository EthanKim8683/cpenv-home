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

const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  string S = "";
  rep(i, 1, 9 + 1) { S += to_string(i); }

  vi D;
  rep(i, 0, sz(S)) {
    rep(j, 1, sz(S) - i + 1) {
      int d = 0;
      for (auto e : S.substr(i, j)) {
        d = d * 10 + e - '0';
      }
      D.pb(d);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    int ans = INF;
    for (auto e : D) {
      if (e >= N) {
        chmin(ans, e);
      }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
