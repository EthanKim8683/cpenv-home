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

  int N, M, K;
  cin >> N >> M >> K;

  vi tickets(N);
  for (auto &e : tickets) cin >> e;

  vi cc;
  for (auto e : tickets) {
    rep(i, max(e - 2, 0ll), min(e + 2, M) + 1) { cc.pb(i); }
  }
  rep(i, 0, M + 1) { cc.pb(i); }
  sort(all(cc));
  cc.erase(unique(all(cc)), cc.end());
  auto compress = [&](int x) -> int {
    return lower_bound(all(cc), x) - cc.begin();
  };

  vc ps1(sz(cc) + 1, vi(2, 0)), ps2 = ps1, ps3 = ps1;
  auto range_add = [&](vc<vi> &ps, int l, int r, int p, int x) -> void {
    ps[l][p] += x;
    ps[r][p] -= x;
  };
  for (auto e : tickets) {
    int i = compress(e);
    range_add(ps1, 0, i, e % 2, 1);
    range_add(ps2, 0, i, e % 2, e / 2);
    range_add(ps3, 0, i, e % 2, -1);
    if (e % 2 == 0) {
      range_add(ps1, 0, i, 1 - e % 2, 1);
      range_add(ps2, 0, i, 1 - e % 2, e / 2);
      range_add(ps3, 0, i, 1 - e % 2, -1);
    } else {
      range_add(ps1, 0, i, 1 - e % 2, 1);
      range_add(ps2, 0, i, 1 - e % 2, 1 + e / 2);
      range_add(ps3, 0, i, 1 - e % 2, -1);
    }
    range_add(ps1, i + 1, sz(cc), e % 2, -1);
    range_add(ps2, i + 1, sz(cc), e % 2, M - e / 2);
    range_add(ps3, i + 1, sz(cc), e % 2, 1);
    if (e % 2 == 0) {
      range_add(ps1, i + 1, sz(cc), 1 - e % 2, -1);
      range_add(ps2, i + 1, sz(cc), 1 - e % 2, M + 1 - e / 2);
      range_add(ps3, i + 1, sz(cc), 1 - e % 2, 1);
    } else {
      range_add(ps1, i + 1, sz(cc), 1 - e % 2, -1);
      range_add(ps2, i + 1, sz(cc), 1 - e % 2, M - e / 2);
      range_add(ps3, i + 1, sz(cc), 1 - e % 2, 1);
    }
  }
  rep(i, 0, sz(cc)) {
    rep(j, 0, 2) {
      ps1[i + 1][j] += ps1[i][j];
      ps2[i + 1][j] += ps2[i][j];
      ps3[i + 1][j] += ps3[i][j];
    }
  }
  int count = 0, best = M + 1;
  rep(i, 0, sz(cc)) {
    cerr << ps1[i][cc[i] % 2] * cc[i] + ps2[i][cc[i] % 2] +
                ps3[i][cc[i] % 2] * (cc[i] / 2)
         << ' ';
    if (ps1[i][cc[i] % 2] * cc[i] + ps2[i][cc[i] % 2] +
            ps3[i][cc[i] % 2] * (cc[i] / 2) >
        N - K) {
      count++;
      chmin(best, i);
    }
  }
  cerr << '\n';
  cerr << count << ' ' << best << '\n';
}
