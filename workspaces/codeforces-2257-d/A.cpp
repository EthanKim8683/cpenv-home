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
    int S, Q;
    cin >> S >> Q;

    vc<pii> queries(Q);
    for (auto &[x, y] : queries) {
      cin >> x >> y;
    }

    vi divisors;
    for (int i = 1; i * i <= S; i++) {
      if (S % i == 0) {
        divisors.pb(i);
        if (S / i != i) {
          divisors.pb(S / i);
        }
      }
    }
    sort(all(divisors));

    vi cc = divisors;
    cc.pb(0);
    vc<tuple<int, int, int>> ranges;
    for (auto [x, y] : queries) {
      int l = 0, r = sz(divisors);
      while (l < r) {
        int m = l + (r - l) / 2;
        S / divisors[m] <= y ? r = m : l = m + 1;
      }
      int l2 = min(l >= 1 ? divisors[l - 1] : 0, x), r2 = x;
      cc.pb(l2);
      cc.pb(r2);
      ranges.eb(l2, r2, l2 * y);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    auto compress = [&](int x) -> int {
      return lower_bound(all(cc), x) - cc.begin();
    };

    vi y(sz(cc), -1);
    for (auto e : divisors) {
      y[compress(e)] = S / e;
    }
    for (int i = sz(cc) - 1; i >= 1; i--) {
      if (y[i - 1] == -1) {
        y[i - 1] = y[i];
      }
    }

    // rep(i, 0, sz(cc) - 1) {
    //   cerr << format("{} ", pair{pii{cc[i], cc[i + 1]}, y[i + 1]});
    // }
    // cerr << '\n';

    vi ps(sz(cc));
    ps[0] = 0;
    rep(i, 0, sz(cc) - 1) {
      ps[i + 1] = ps[i] + (cc[i + 1] - cc[i]) * y[i + 1];
    }

    for (auto [l, r, c] : ranges) {
      cout << ps[compress(r)] - ps[compress(l)] + c << '\n';
    }
  }
}
