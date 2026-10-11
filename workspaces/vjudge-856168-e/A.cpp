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

const int LOGX = 29;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int X;
    cin >> X;

    if (X % 2 == 1) {
      cout << "-1\n";
      continue;
    }

    int a = 0, b = 0;
    bool ok = true;
    rep(i, 0, LOGX) {
      if (X >> (i + 1) & 1) {
        if (X >> i & 1) {
          ok = false;
          break;
        }
        a |= 3 << i;
        b |= 1 << i;
      }
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }
    cout << a << ' ' << b << '\n';
  }
}
