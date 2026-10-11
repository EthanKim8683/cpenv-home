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

  // after op 3, do op 1 until equal
  // do we ever want to do both op 1 and 2 before op 3?
  // no

  int T;
  cin >> T;

  while (T--) {
    int A, B;
    cin >> A >> B;

    int ans = B - A;
    rep(i, 0, B + 1) {
      chmin(ans, i + 1 + ((A + i) | B) - B);
      chmin(ans, i + 1 + (A | (B + i)) - (B + i));
    }
    cout << ans << '\n';
  }
}
