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

    auto win = [&](int x) -> bool { return __builtin_popcountll(x) % 2 == 0; };

    auto split = [&](int x) -> pii {
      int y = 1ll << __lg(x);
      return {x ^ y, y};
    };

    if (win(N)) {
      cout << "first" << endl;

      auto [x, y] = split(N);
      cout << x << ' ' << y << endl;

      while (true) {
        int p1, p2;
        cin >> p1 >> p2;
        if (p1 == 0 and p2 == 0) break;

        int n;
        if (win(p1)) {
          n = p1;
        } else {
          n = p2;
        }

        auto [x, y] = split(n);
        cout << x << ' ' << y << endl;
      }
    } else {
      cout << "second" << endl;

      while (true) {
        int p1, p2;
        cin >> p1 >> p2;
        if (p1 == 0 and p2 == 0) break;

        int n;
        if (win(p1)) {
          n = p1;
        } else {
          n = p2;
        }

        auto [x, y] = split(n);
        cout << x << ' ' << y << endl;
      }
    }
  }
}
