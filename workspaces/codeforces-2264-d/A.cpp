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
    int N;
    cin >> N;

    if (N < 3) {
      cout << string(N, '1') << '\n';
      continue;
    }

    tuple<int, int, int, int, int> ans = {INF, -1, -1, -1, -1};
    auto use = [&](int a, int b, int c, int d) -> void {
      if (a < 0 or b < 0 or c < 0 or d < 0) return;
      if (a + 1 + b + 1 + c + 1 + d != N) return;
      chmin(ans, tuple{a * (a + 1) / 2 + b * (b + 1) / 2 + c * (c + 1) / 2 +
                           d * (d + 1) / 2 + (a + 1) * (d + 1),
                       a, b, c, d});
    };
    rep(i, 0, (N - 3) / 2 + 1) {
      int j = ((N - 3) - 2 * i) / 2;
      rep(k, -2, 2 + 1) {
        rep(l, -2, 2 + 1) {
          rep(m, -2, 2 + 1) {
            rep(n, -2, 2 + 1) { use(i + k, j + l, j + m, i + n); }
          }
        }
      }
    }
    auto [cost, a, b, c, d] = ans;
    cout << string(a, '0') + '1' + string(b, '0') + '1' + string(c, '0') + '1' +
                string(d, '0')
         << '\n';
  }
}
