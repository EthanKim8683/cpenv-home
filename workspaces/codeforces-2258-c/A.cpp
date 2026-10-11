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

    auto query = [&](int u, int v, int d) -> bool {
      cout << "? " << u + 1 << ' ' << v + 1 << ' ' << d << endl;
      int ge;
      cin >> ge;
      if (ge == -1) {
        exit(0);
      }
      return ge == 1;
    };

    auto answer = [&](int u, int v, int d) -> void {
      cout << "! " << u + 1 << ' ' << v + 1 << ' ' << d << endl;
    };

    int a = 0, b = 1, d = 1;
    while (d + 1 <= N - 1 and query(a, b, d + 1)) {
      d++;
    }
    rep(c, 2, N) {
      int da = d;
      while (da + 1 <= N - 1 and query(a, c, da + 1)) {
        da++;
      }
      int db = da;
      while (db + 1 <= N - 1 and query(b, c, db + 1)) {
        db++;
      }
      if (db > da) {
        if (db > d) {
          a = c;
          d = db;
        }
      } else {
        if (da > d) {
          b = c;
          d = da;
        }
      }
    }
    answer(a, b, d);
  }
}
