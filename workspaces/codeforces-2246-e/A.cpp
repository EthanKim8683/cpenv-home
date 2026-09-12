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

  mt19937_64 rng(time(nullptr));

  int T;
  cin >> T;

  while (T--) {
    int x = (1 << 30) - 2;
    cout << x << endl;

    int O;
    cin >> O;

    if (O != x) {
      int m0 = 0, m1 = (1 << 30) - 1;
      cout << m0 << ' ' << m1 << endl;

      int R;
      cin >> R;

      int ans;
      if (O > x) {
        ans = ((R ^ m0) & ~x) == (O & ~x) ? 0 : 1;
      } else {
        ans = ((R ^ m0) & x) == (O & x) ? 0 : 1;
      }
      cout << ans << endl;
      continue;
    }

    int m0 = 1, m1 = rng() & x;
    cout << m0 << ' ' << m1 << endl;

    int R;
    cin >> R;

    // if all 1's:
    // V ^ m0 ^ m0 = all 1's
    // V ^ m1 ^ m0 = subset
    // V ^ m1 ^ m1 = all 1's
    //
    // if subset:
    // V ^ m0 ^ m0 = subset
    // V ^ m0 ^ m1 = invalid (or all 1's; P = 2^{-29})
    // V ^ m1 ^ m0 = invalid (or all 1's; P = 2^{-29})

    auto is_subset = [&](int v) -> bool { return (v & x) == v; };

    int ans;
    if ((R ^ m0) == (1 << 30) - 1) {
      ans = 0;
    } else if (is_subset(R ^ m0)) {
      if ((R ^ m1) == (1 << 30) - 1) {
        ans = 1;
      } else {
        ans = 0;
      }
    } else {
      ans = 1;
    }
    cout << ans << endl;
  }
}
