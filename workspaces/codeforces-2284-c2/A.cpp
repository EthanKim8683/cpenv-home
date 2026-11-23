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

const int MAXB = 1e5 + 500;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi primes;
  vc<bool> is_prime(MAXB + 1, true);
  rep(i, 2, MAXB + 1) {
    if (is_prime[i]) {
      primes.pb(i);
    }
    for (auto e : primes) {
      if (i * e > MAXB) break;
      is_prime[i * e] = false;
      if (i % e == 0) {
        break;
      }
    }
  }

  // int worst = 0;
  // rep(i, 1, sz(primes) - 1) {
  //   int A = primes[i] + 1, B = primes[i + 1] - 1;

  //   int d = B - A;

  //   pii nil = {INF, -1};
  //   vc<pii> dp(d + 1, nil);
  //   dp[0] = {0, -1};
  //   rep(i, 0, d) {
  //     if (dp[i] == nil) continue;
  //     rep(j, 1, d - i + 1) {
  //       if (gcd(A + i, j) != 1) continue;
  //       chmin(dp[i + j], pii{dp[i].fs + 1, j});
  //     }
  //   }
  //   assert(dp[d] != nil);

  //   vi ans;
  //   for (int i = d; i != 0; i -= dp[i].sd) {
  //     ans.pb(dp[i].sd);
  //   }
  //   reverse(all(ans));

  //   int a = A;
  //   for (auto e : ans) {
  //     assert(gcd(a, e) == 1);
  //     a += e;
  //   }
  //   assert(a == B);

  //   chmax(worst, dp[d].fs);
  // }
  // cerr << worst << '\n';

  int T;
  cin >> T;

  while (T--) {
    int A, B;
    cin >> A >> B;

    int d = B - A;
    if (gcd(A, d) == 1) {
      cout << "1\n" << d << '\n';
      continue;
    }

    int p = *upper_bound(all(primes), A);
    if (p <= B) {
      vi ans;
      while (B % p == 0) {
        p = *upper_bound(all(primes), p);
      }
      ans.pb(p - A);
      ans.pb(B - p);
      cout << sz(ans) << '\n';
      for (auto e : ans) {
        cout << e << ' ';
      }
      cout << '\n';

      int a = A;
      for (auto e : ans) {
        assert(gcd(a, e) == 1);
        a += e;
      }
      assert(a == B);
      continue;
    }

    pii nil = {INF, -1};
    vc<pii> dp(d + 1, nil);
    dp[0] = {0, -1};
    rep(i, 0, d) {
      if (dp[i] == nil) continue;
      rep(j, 1, d - i + 1) {
        if (gcd(A + i, j) != 1) continue;
        chmin(dp[i + j], pii{dp[i].fs + 1, j});
      }
    }
    assert(dp[d] != nil);

    vi ans;
    for (int i = d; i != 0; i -= dp[i].sd) {
      ans.pb(dp[i].sd);
    }
    reverse(all(ans));
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';

    int a = A;
    for (auto e : ans) {
      assert(gcd(a, e) == 1);
      a += e;
    }
    assert(a == B);
  }
}
