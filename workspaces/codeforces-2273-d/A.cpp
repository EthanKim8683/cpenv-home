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

const int MAXX = 1e4;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // after round 1, we know adding or subtracting x to both a and b will result
  // in 0 aura loss
  //
  // if we make a0 = 1/4th between -1e9 and 1e9 and b0 = 3/4ths, we can minimize
  // our first cost to be at most 2e9/4. is this m?
  //
  // say our first cost is exactly 2e9/4. it must be either the ends or the
  // middle.
  //
  // actually, maybe this is not ideal because it gives 3 peaks, which is hard
  // to handle with 2 numbers
  //
  // an observation is that, after the answer to round 1, we get 4 candidate x's
  //
  // maybe a small peak in the middle is a decent tradeoff because costs greater
  // than the peak can be instasolved. costs no greater than the peak can be
  // solved trivially in at most 3 * peak total?
  //
  // we want the max total of everything to be below a certain value
  //
  // we can do 2 * peak + 1 total? if this is the case, we'd want peak to be
  // half the outside max. basically we divide everything into thirds, making m
  // = ~2e9/3. can we show that this is a lower bound?
  //
  // there are only two cases: 2 x's or >2 x's. the >2 x's case cannot be solved
  // in cheaper than ~2 * peak because we cannot move a and b in such a way that
  // the maximum distance to any of the 3-4 x's doesn't increase
  //
  // wait 1 <= x <= 1e4. i'm stupid. idea still stands though
  //
  // shit it's minimum distance. i think what i said still stands though
  //
  // hm. what if we looked at this asymmetrically, because cost > peak -> free
  // as usual (peaks at cost), smaller boundary < cost <= peak is kind of cheap
  // (peaks at cost+(peak-cost)+1 = peak+1, then cost <=
  // smaller boundary has 4 x's but they're fairly close so it maxes out at
  // 2*smaller boundary+1
  //
  // so now it's about picking smaller boundary and peak optimally?

  tuple<int, int, int> best = {INF, -1, -1};
  for (int a = 1; a <= MAXX; a++) {
    for (int b = a; b <= MAXX; b += 2) {
      int l = a - 1, m = (b - a) / 2, r = MAXX - b;
      if (l <= m and m <= r) {
        chmin(best, tuple{max(r, max(m + 1, 2 * l + 1)), a, b});
      }
    }
  }
  auto [cost, a, b] = best;
  int l = a - 1, m = (b - a) / 2, r = MAXX - b;
  // cerr << cost << '\n';

  int T;
  cin >> T;

  while (T--) {
    auto choose = [&](int a, int b) -> int {
      cout << a << ' ' << b << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    // int a0 = 1 + (MAXX - 1) / 3, b0 = MAXX - (MAXX - 1) / 3;

    // int y = choose(a0, b0);
    // if (y > 1 + (MAXX - 1) / 2 - a0) {
    //   rep(i, 1, 10) { choose(a0 - y, b0 + y); }
    // } else {
    //   if (choose(a0 + 1, b0 + 1) > y) {
    //     rep(i, 2, 10) { choose(a0 - y, b0 - y); }
    //   } else {
    //     rep(i, 2, 10) { choose(a0 + y, b0 + y); }
    //   }
    // }

    int y = choose(a, b);
    if (y > m) {
      rep(i, 1, 10) { choose(b + y, 0); }
    } else if (y > l) {
      if (choose(a + m + 1, b + y) > m - y) {
        rep(i, 2, 10) { choose(a + y, 0); }
      } else {
        rep(i, 2, 10) { choose(b - y, b + y); }
      }
    } else {
      if (choose(a + 1, b + 1) > y) {
        rep(i, 2, 10) { choose(a - y, b - y); }
      } else {
        rep(i, 2, 10) { choose(a + y, b + y); }
      }
    }
  }
}
