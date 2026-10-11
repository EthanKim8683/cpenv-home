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

const int MAXA = 1e6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi primes, sieve(MAXA + 1), labels(MAXA + 1);
  vc<bool> is_prime(MAXA + 1, true);
  labels[1] = 1;
  for (int i = 2; i <= MAXA; i++) {
    if (is_prime[i]) {
      labels[i] = i;
      sieve[i] = i;
      primes.pb(i);
    }
    for (auto e : primes) {
      if (i * e > MAXA) break;
      is_prime[i * e] = false;
      sieve[i * e] = e;
      if (i % e == 0) {
        if (labels[i] % e == 0) {
          labels[i * e] = labels[i] / e;
        } else {
          labels[i * e] = labels[i] * e;
        }
        break;
      } else {
        labels[i * e] = labels[i] * e;
      }
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    map<int, int> counts;
    for (auto e : A) {
      counts[labels[e]] += 1;
    }

    set<int> primes;
    int ans = 0;
    for (auto e : A) {
      for (int i = e; i != 1; i /= sieve[i]) {
        if (primes.contains(sieve[i])) {
          primes.erase(sieve[i]);
        } else {
          primes.insert(sieve[i]);
        }
      }
      int prod = 1;
      for (auto e : primes) {
        prod *= e;
        if (prod > MAXA) break;
      }
      if (prod <= MAXA) {
        ans += counts[prod];
      }
    }
    cout << ans << '\n';
  }
}
