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

  // alice nukes some piles with sum <= k
  // if bob went before, alice has to get all of bob's piles
  //
  // bob picks <= k piles
  //
  // if it's impossible for alice to pick piles such that the bob cannot pick up
  // to k piles with sum greater than k + (# of piles), then alice loses
  //
  // bob always beats alice immediately since the state only gets worse and the
  // moves stay the same
  //
  // bob doesn't actually always beat alice immediately because he can force
  // alice to make a losing move
  //
  // say there's a pile alice can't take out in one go. bob can force alice to
  // take this pile by taking a 1
  //
  // alice can also postpone by taking a 1. perhaps it's a nim game until the
  // main game, where there's no 1's
  //
  // say the main game's a losing game for alice. does it become a losing game
  // for bob? no not really. it may be a losing game, it may not
  //
  // i think the nim game thing is still useful. let's do casework:
  // if alice wins when she starts:
  //   if bob wins when he starts:
  //     it's misere nim
  //   else:
  //     alice must win
  // else:
  //   if bob wins when he starts:
  //     bob must win
  //   else:
  //     it's nim
  //
  // how do we check if bob wins when he starts? bob picks up to k piles and he
  // aims for a sum - (# of piles) greater than k.
  //
  // it's not exactly nim and misere nim, though, because we want to remove
  // between 1 and k one-piles. for nim, it's easy. if it's 0 modulo k+1, then
  // alice loses
  //
  // for misere nim, if it's 1 modulo k+1, then alice loses? let's prove this:
  // base case: 0 is win
  // losing -> winning: must make it not 1 mod k+1
  // winning -> losing: starts at not 1 mod k+1, can make 1 mod k+1

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vc<bool> seen(N, false);
    auto dfs = [&](auto self, int a) -> int {
      if (seen[a]) return 0;
      seen[a] = true;
      int rv = 1;
      rv += self(self, P[a]);
      return rv;
    };
    vi groups;
    rep(i, 0, N) {
      if (seen[i]) continue;
      groups.pb(dfs(dfs, i));
    }

    sort(all(groups));
    reverse(all(groups));

    int ones = 0;
    while (sz(groups) > 0 and groups.back() == 1) {
      ones++;
      groups.pop_back();
    }

    int M = sz(groups);

    bool ok;
    if (M == 0) {
      ok = true;
    } else {
      vc dp(M + 1, vc(K + 1, vc(K + 1, vi(2, INF))));
      dp[0][0][0][0] = 0;
      rep(i, 0, M) {
        rep(j, 0, K + 1) {
          rep(k, 0, K + 1) {
            rep(l, 0, 2) {
              if (j + groups[i] <= K) {
                chmin(dp[i + 1][j + groups[i]][k][1], dp[i][j][k][l]);
              }
              if (k + 1 <= K) {
                chmin(dp[i + 1][j][k + 1][l], dp[i][j][k][l] + groups[i] - 1);
              } else {
                chmin(dp[i + 1][j][k][l], dp[i][j][k][l]);
              }
            }
          }
        }
      }
      int best = INF;
      for (auto r : dp[M]) {
        for (auto e : r) {
          chmin(best, e[1]);
        }
      }
      ok = best <= K;
    }

    int best2 = 0;
    rep(i, 0, min(M, K)) { best2 += groups[i] - 1; }
    bool ok2 = best2 > K;

    if (ok and !ok2) {
      cout << "Alice\n";
      continue;
    }

    if (!ok and ok2) {
      cout << "Bob\n";
      continue;
    }

    if (ok and ok2) {
      cout << (ones % (K + 1) == 1 ? "Bob" : "Alice") << '\n';
      continue;
    }

    cout << (ones % (K + 1) == 0 ? "Bob" : "Alice") << '\n';
  }
}
