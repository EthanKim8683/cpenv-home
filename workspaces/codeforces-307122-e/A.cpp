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

const string ABCD = "ABCD";

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi counts(4);
  for (auto &e : counts) {
    cin >> e;
  }

  vc ans(50, string(50, ' '));
  vc<vc<pii>> dots(4);
  rep(i, 0, 50) {
    rep(j, 0, 50) {
      int q = i / 25 * 2 + j / 25;
      ans[i][j] = ABCD[q];
      if ((i - i / 25) % 2 == 1 and (j - j / 25) % 2 == 1) {
        dots[(q + 1) % 4].eb(i, j);
      }
    }
  }
  rep(i, 0, 4) {
    rep(j, 0, counts[i] - 1) {
      auto [k, l] = dots[i][j];
      ans[k][l] = ABCD[i];
    }
  }
  cout << "50 50\n";
  for (auto e : ans) {
    cout << e << '\n';
  }
}
