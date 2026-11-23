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

const int MAXA = 1e5;
const int MAXB = 1e5 + 500;

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

  rep(i, 0, sz(primes) - 1) { assert(primes[i + 1] <= 2 * primes[i]); }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    for (auto e : A) {
      cout << *lower_bound(all(primes), e) << ' ';
    }
    cout << '\n';
  }
}
