#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

const int INF = 2e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<pii> col1(N);
    for (auto &[l, r] : col1) {
      cin >> l >> r;
      r++;
    }

    vc<pii> col2(M);
    for (auto &[l, r] : col2) {
      cin >> l >> r;
      r++;
    }

    vc<pii> col3;
    for (auto [l, r] : col1) {
      auto it = upper_bound(all(col2), pii{l, INF});
      if (it != col2.begin() and prev(it)->sd >= r) continue;
      col3.eb(l, r);
    }
    vc<pii> col4;
    for (auto [l, r] : col2) {
      auto it = upper_bound(all(col3), pii{l, INF});
      if (it != col3.begin() and prev(it)->sd >= r) continue;
      col4.eb(l, r);
    }
    vc<pii> ranges;
    ranges.insert(ranges.end(), all(col3));
    ranges.insert(ranges.end(), all(col4));
    sort(all(ranges));

    vi cc;
    for (auto [l, r] : ranges) {
      cc.pb(l);
      cc.pb(r);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    auto compress = [&](int x) -> int {
      return lower_bound(all(cc), x) - cc.begin();
    };

    vc<vi> trans(sz(cc));
    auto add_trans = [&](int a, int b) -> void {
      a = compress(a);
      b = compress(b);
      if (a >= b) return;
      trans[a].pb(b);
    };
    rep(i, 0, sz(ranges)) {
      auto [l, r] = ranges[i];
      if (i + 1 < sz(ranges)) {
        auto [l2, r2] = ranges[i + 1];
        if (l2 < r) {
          add_trans(l, l2);
          add_trans(l, r);
          add_trans(r, r2);
          if (i + 2 < sz(ranges)) {
            auto [l3, r3] = ranges[i + 2];
            if (r < l3 and l3 < r2) {
              add_trans(r, l3);
            }
          }
          continue;
        }
      }
      add_trans(l, r);
    }

    auto insert = [&](vi &v, int x) -> void {
      int i = 0;
      for (; i < sz(v); i++) {
        if (x >= v[i]) break;
      }
      v.insert(v.begin() + i, x);
    };

    vc<vi> dp(4);
    rep(i, 0, sz(cc)) {
      for (auto e : trans[i]) {
        auto dp2 = dp[i % 4];
        assert(e - i <= 3);
        insert(dp2, cc[e] - cc[i]);
        chmax(dp[e % 4], dp2);
      }
      chmax(dp[(i + 1) % 4], dp[i % 4]);
    }
    auto ans = dp[(sz(cc) - 1) % 4];
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
