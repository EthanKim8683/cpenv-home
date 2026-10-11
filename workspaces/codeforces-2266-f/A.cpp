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

const int MAXY = 1e9;
const int LOGNY = 48;

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

    vc<pii> counts(N);
    for (auto &[x, y] : counts) {
      cin >> x >> y;
    }

    vi counts2(N + LOGNY + 1, 0);
    for (auto [x, y] : counts) {
      if (x > N + LOGNY) {
        counts2[0] += y;
      } else {
        counts2[x] = y;
      }
    }

    auto check = [&](int x) -> bool {
      int z = counts2[0];
      rep(i, x, N + LOGNY + 1) { z += counts2[i]; }
      int le = 1;
      for (int i = x - 1; i > 0; i--) {
        if (le > counts2[i]) {
          le += le - counts2[i];
        } else {
          z += counts2[i] - le;
        }
        if (le > N * MAXY) return false;
      }
      return le <= z;
    };
    int l = 0, r = N + LOGNY;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << max(l, max_element(all(counts))->fs) << '\n';
  }
}
