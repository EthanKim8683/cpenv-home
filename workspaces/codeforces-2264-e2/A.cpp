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

const int MAXN = 300000;
const int MOD = 998244353;
const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // say our target element is x. basically we spam all primes that aren't
  // divisors of x and i guess this makes everything x. well. that is, unless
  // there are other elements which have the exact same prime divisor set as x.
  //
  // if that's the case, then let's say we just leave those ones alone, since we
  // can't get x anyway, but we want to get everything else as close to whatever
  // value we're after.
  //
  // then we decrease everything by one and i think all elements should have
  // prime factors excluded in the minimum? actually, i don't this this even
  // matters. what matters is the minimum prime factor of the minimum, since all
  // other elements would have to go through that anyway. or actually, more than
  // the minimum prime factor, there's levels.
  //
  // i think we just need to keep track of the minimum and maximum elements of
  // the subsequences, though. i wonder if there are that many multiples for
  // each minimum, because that would free up a nice DP. actually, there aren't!
  // in total it's like O(nlogn).
  //
  // okay sweet. i think we now need to find how subsequences map onto this.
  // maybe sort A, pick minimums and bucket the rest under multiples.
  //
  // 2^(r1-l-1) + 2^(r2-l-1) + ... + 2^(rk-l-1) = 2^(rk-l) - 2^(r1-l-1)
  //
  // hm. we need to deal with duplicate minimums. we can multiply by 2^k-1,
  // where k is the chunk size.
  //
  // actually, what i've been calling "multiples" don't have to be multiples at
  // all. all that's required is that the greater number's set of primes is a
  // subset of the smaller number's. i think this breaks the O(nlogn) complexity
  // i was hoping for.
  //
  // however, i imagine the actual DP values themselves don't change much. so
  // perhaps we can use this to our advantage. let's group up the numbers by
  // prime factor sets, then binary search for significant maximums. actually,
  // how sure am i that they don't change much? if i is prime, dp[i] has log(N)
  // unique values. dp[i+1] transitions from that, so it can only have at most
  // log(N) significant maximums.

  vc<bool> is_prime(MAXN + 1, true);
  vi sets(MAXN + 1);
  sets[1] = 1;
  vc<vi> subsets(MAXN + 1);
  subsets[1].pb(1);
  vi primes;
  rep(i, 2, MAXN + 1) {
    if (is_prime[i]) {
      sets[i] = i;
      subsets[i].pb(1);
      subsets[i].pb(i);
      primes.pb(i);
    }
    for (auto e : primes) {
      if (i * e > MAXN) break;
      is_prime[i * e] = false;
      if (i % e == 0) {
        sets[i * e] = sets[i];
        break;
      } else {
        sets[i * e] = sets[i] * e;
        for (auto e2 : subsets[i]) {
          subsets[i * e].pb(e2);
          subsets[i * e].pb(e2 * e);
        }
      }
    }
  }

  vc<vi> groups(MAXN + 1);
  rep(i, 1, MAXN + 1) { groups[sets[i]].pb(i); }

  vc<vc<pii>> dp(MAXN + 1);
  rep(i, 1, MAXN + 1) {
    dp[i].eb(i, i);
    for (auto [j, x] : dp[i - 1]) {
      chmax(j, i);
      int k = INF;
      for (auto e : subsets[sets[i]]) {
        auto it = upper_bound(all(groups[e]), j);
        if (it == groups[e].end()) continue;
        chmin(k, *it);
      }
      if (dp[i].back().fs != k) {
        dp[i].eb(k, x);
      } else {
        dp[i].back().sd = x;
      }
    }
  }

  vi pows(MAXN + 1);
  pows[0] = 1;
  rep(i, 1, MAXN + 1) { pows[i] = pows[i - 1] * 2 % MOD; }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    sort(all(A));

    map<int, int> counts;
    for (auto e : A) {
      counts[e] += 1;
    }

    int ans = 0;
    for (auto [x, count] : counts) {
      rep(i, 0, sz(dp[x])) {
        auto [l, w] = dp[x][i];
        if (l > N) break;

        int r;
        if (i + 1 >= sz(dp[x])) {
          r = INF;
        } else {
          r = dp[x][i + 1].fs;
        }

        int contrib;
        if (l == x) {
          int n = lower_bound(all(A), r) - upper_bound(all(A), x);
          contrib = (pows[count] - 1) % MOD * pows[n] % MOD;
        } else {
          int n1 = lower_bound(all(A), l) - upper_bound(all(A), x),
              n2 = lower_bound(all(A), r) - lower_bound(all(A), l);
          contrib =
              (pows[count] - 1) % MOD * pows[n1] % MOD * (pows[n2] - 1) % MOD;
        }
        (ans += w * contrib) %= MOD;
      }
    }
    (ans += MOD) %= MOD;
    cout << ans << '\n';
  }
}
