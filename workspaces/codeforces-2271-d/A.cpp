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

const int MAXS = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vc<pii> ranges(N);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
      r++;
    }

    if (K == 0) {
      cout << MAXS << '\n';
      continue;
    }

    vi cc;
    cc.pb(1);
    cc.pb(MAXS);
    for (auto [l, r] : ranges) {
      cc.pb(l - M);
      cc.pb(l);
      cc.pb(r - M);
      cc.pb(r);
    }
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());

    auto compress = [&](int x) -> int {
      return lower_bound(all(cc), x) - cc.begin();
    };

    vi ps(sz(cc), 0);
    for (auto [l, r] : ranges) {
      ps[compress(l - M)] += 1;
      ps[compress(l)] -= 1;
      ps[compress(r - M)] -= 1;
      ps[compress(r)] += 1;
    }
    rep(i, 0, sz(cc) - 1) { ps[i + 1] += ps[i]; }

    int sum = 0, ans = -1;
    rep(i, 0, sz(cc) - 1) {
      if (ps[i] == 0) {
        if (sum == K) {
          int l = max(cc[i], 1ll), r = min(cc[i + 1], MAXS);
          if (l <= r) {
            ans = l;
          }
        }
      } else {
        if ((K - sum) % ps[i] == 0) {
          int d = (K - sum) / ps[i];
          if (0 < d and d <= cc[i + 1] - cc[i]) {
            int s = cc[i] + d;
            if (1 <= s and s <= MAXS) {
              ans = s;
            }
          }
        }
      }
      sum += (cc[i + 1] - cc[i]) * ps[i];
    }
    cout << ans << '\n';
  }
}
