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

const int INF = 1e9;
const int LOGN = 18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, Q;
  cin >> N >> Q;

  vi P(N);
  for (auto &e : P) {
    cin >> e;
    e--;
  }

  // while (Q--) {
  //   int l, r;
  //   cin >> l >> r;
  //   l--;

  //   vc<pii> ranges;
  //   int l2 = l;
  //   rep(i, l, r - 1) {
  //     if (P[i] < P[i + 1]) {
  //       ranges.eb(l2, i + 1);
  //       l2 = i + 1;
  //     }
  //   }
  //   ranges.eb(l2, r);

  //   int p = -INF, ans = 0;
  //   for (auto [l2, r2] : ranges) {
  //     int x = INF;
  //     rep(i, l2, r2) {
  //       if (P[i] > p) {
  //         chmin(x, P[i]);
  //       }
  //     }
  //     if (x == INF) {
  //       ans += 1;
  //       p = P[l2 - 1];
  //       rep(i, l2, r2) {
  //         if (P[i] > p) {
  //           chmin(x, P[i]);
  //         }
  //       }
  //     }
  //     ans += 1;
  //     p = x;
  //   }
  //   cout << ans << '\n';
  // }

  vi groups(N);
  vc<pii> ranges;
  int l = 0;
  rep(i, 0, N) {
    groups[i] = sz(ranges);
    if (i + 1 < N and P[i] < P[i + 1]) {
      ranges.eb(l, i + 1);
      l = i + 1;
    }
  }
  ranges.eb(l, N);

  vi Pinv(N);
  rep(i, 0, N) { Pinv[P[i]] = i; }

  vc anc(N + 1, vc<pii>(LOGN + 1));
  anc[N][0] = {N, 0};
  vi mins(sz(ranges), INF);
  for (int p = N - 1; p >= 0; p--) {
    int i = Pinv[p], g = groups[i];
    if (g + 1 < sz(ranges)) {
      int p2 = mins[g + 1];
      if (p2 == INF) {
        anc[i][0] = {ranges[g].sd - 1, 1};
      } else {
        int j = Pinv[p2];
        anc[i][0] = {j, 1};
      }
    } else {
      anc[i][0] = {N, 0};
    }
    mins[g] = p;
  }
  rep(i, 1, LOGN + 1) {
    rep(j, 0, N + 1) {
      auto [p1, d1] = anc[j][i - 1];
      auto [p2, d2] = anc[p1][i - 1];
      anc[j][i] = {p2, d1 + d2};
    }
  }

  while (Q--) {
    int l, r;
    cin >> l >> r;
    l--;

    if (groups[l] == groups[r - 1]) {
      cout << "1\n";
      continue;
    }

    int a = ranges[groups[l]].sd - 1, ans = 2;
    for (int i = LOGN; i >= 0; i--) {
      if (anc[a][i].fs < ranges[groups[r - 1]].fs) {
        auto [p, d] = anc[a][i];
        a = p;
        ans += d;
      }
    }
    if (P[a] > P[ranges[groups[r - 1]].fs]) {
      ans += 1;
    }
    cout << ans << '\n';
  }
}
