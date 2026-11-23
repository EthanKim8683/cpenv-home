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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // convert each number to a square-free form
  //
  // sqrt decomp?? like what pendy did
  //
  // split number into big prime, then small primes
  //
  // pick two numbers with same big prime, then a number with no big prime. the
  // number with no big prime should satisfy the xor of the first two numbers
  //
  // actually let's extend to general leading primes

  vi primes, sieve(MAXN + 1);
  vc<bool> is_prime(MAXN + 1, true);
  rep(i, 2, MAXN + 1) {
    if (is_prime[i]) {
      primes.pb(i);
      sieve[i] = i;
    }
    for (auto e : primes) {
      if (i * e > MAXN) break;
      is_prime[i * e] = false;
      if (i % e == 0) {
        sieve[i * e] = e;
        break;
      }
      sieve[i * e] = e;
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<map<int, int>> by_leading_prime(N + 1);
    map<int, int> counts;
    rep(i, 1, N) {
      vi primes;
      primes.pb(1);
      for (int x = i; x != 1; x /= sieve[x]) {
        if (sz(primes) > 0 and primes.back() == sieve[x]) {
          primes.pop_back();
        } else {
          primes.pb(sieve[x]);
        }
      }
      int x = 1;
      rep(j, 0, sz(primes) - 1) { x *= primes[j]; }
      by_leading_prime[primes.back()][x] += 1;
      x *= primes.back();
      counts[x] += 1;
    }
    int ans = 0;
    for (auto r : by_leading_prime) {
      ans += sz(r) * sz(r);
      // for (auto e1 : r) {
      //   for (auto e2 : r) {
      //     int x = lcm(e1, e2) / gcd(e1, e2);
      //     if (x > N) continue;
      //     ans += counts[x];
      //   }
      // }
    }
    cout << ans << '\n';
  }
}
