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

const int MAXN = 1e6;
const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // all components have a maximum number of nodes that can be outside the
  // starting set
  //
  // 1. pick the smallest available node
  // 2. pick k available nodes
  // 3. make a component
  //
  // we should pre-solve the distribution of maximum number of nodes of
  // components by size
  //
  // then we could probably fft..? nah let's dig deeper first
  //
  // actually, it'd be pretty tricky to guarantee a connected component...
  //
  // let's just see the distribution of maximum number of nodes across all
  // components in total
  //
  // make a certain set of nodes interior:
  // if k nodes are interior, there are binom(N+k-1,k-1)*N! graphs, but this
  // allows self-loops
  // this also doesn't address how cycles consist entirely of interior nodes but
  // still need a starting set node
  //
  // let's dedicate some nodes to cycles, and some nodes to non-cycles
  // the cycle nodes require x starting set nodes, where x is the number of
  // cycles
  // the non-cycles require all the exterior nodes to be starting set nodes
  //
  // maybe i'm thinking about the structure too much. let's try to simulate
  // something
  // 1. pick an unused node and start at it
  // 2. pick a different node to go to
  //    if it's used, stop
  //    else, decide if it'll be in the starting set
  // 3. go back to step 2
  //
  // i like this and i think it'll make for an alright DP
  //
  // actually, this doesn't account for component order
  // but, if we modify it a bit: starting with the minimum node and giving the
  // option to end at it... eh
  //
  // how about we keep track of the number of nodes that need an incoming
  // starting node, and the number of nodes that need an outgoing node and then
  // just process the nodes in order? this is okay but cycles need to know if
  // they have a starting set node or not
  //
  // what if we process starting nodes in increasing order and paths end at
  // nodes already visited

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    auto mod_pow = [&](int x, int y) -> int {
      int rv = 1;
      for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
        if (y & 1) {
          (rv *= x) %= MOD;
        }
      }
      return rv;
    };

    auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

    auto binom = [&](int n, int k) -> int {
      return fact[n] * mod_inv(fact[n - k] * fact[k]) % MOD;
    };

    // // [# nodes visited][# starting nodes visited][starting path?]
    // vc dp(N + 1, vc(M + 1, vi(2, 0)));
    // dp[0][0][1] = binom(N, M);
    // rep(i, 0, N) {
    //   rep(j, 0, M + 1) {
    //     // starting path
    //     // visit unvisited non-starting node
    //     if (j + 1 <= M) {
    //       (dp[i + 1][j + 1][0] += dp[i][j][1] * ((N - M) - (i - j))) %= MOD;
    //     }
    //     // visit visited or starting node (except current node)
    //     if (j + 1 <= M) {
    //       (dp[i + 1][j + 1][1] += dp[i][j][1] * (i + (M - j - 1))) %= MOD;
    //     }

    //     // continuing path
    //     // visit unvisited non-starting node (except current node)
    //     (dp[i + 1][j][0] += dp[i][j][0] * ((N - M) - (i - j + 1))) %= MOD;
    //     // visit visited or starting node
    //     (dp[i + 1][j][1] += dp[i][j][0] * (i + (M - j))) %= MOD;
    //   }
    // }
    // cout << dp[N][M][1] << '\n';

    // visit unvisited or visit visited
    // visit visited exactly M times
    // can we use pie to exclude self loops?
    //
    // or maybe each starting node gets a "tail" and then the tail is allowed to
    // connect to any node in the tail of a starting node not before its own
    // (excluding itself, of course)

    // vc dp(M + 1, vi(N + 1, 0));
    // dp[0][0] = binom(N, M) * fact[N - M] % MOD;
    // rep(i, 0, M) {
    //   rep(j, 0, N + 1) {
    //     rep(k, 1, N - j + 1) {
    //       (dp[i + 1][j + k] += dp[i][j] * (M - i - 1 + j + k - 1)) %= MOD;
    //     }
    //   }
    // }
    // cout << dp[M][N] << '\n';

    int ans = 0;
    rep(i, 0, M + 1) {
      int add = 1;
      (add *= fact[i]) %= MOD;
      (add *= binom(M + i - 1 + M, i + M)) %= MOD;
      (add *= mod_inv(mod_pow(2, 2 * i))) %= MOD;
    }
    (ans *= binom(N, M)) %= MOD;
    (ans *= fact[N - M]) %= MOD;
    cout << ans << '\n';
  }
}
