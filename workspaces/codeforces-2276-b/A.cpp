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
    string S;
    cin >> S;

    vi groups;
    for (int i = 0, j; i < sz(S); i = j) {
      for (j = i; j < sz(S); j++) {
        if (S[j] != S[i]) break;
      }
      groups.pb(j - i);
    }

    set<int> sizes;
    sizes.insert(sz(S));
    rep(i, 1, sz(groups) - 1) {
      if (groups[i] == 1) {
        sizes.insert(sz(S) - 2);
      }
    }
    for (auto e : groups) {
      if (e >= 3) {
        sizes.insert(sz(S) + 2);
      }
    }
    cout << sz(sizes) << '\n';
  }
}
