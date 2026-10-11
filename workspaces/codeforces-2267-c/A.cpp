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

const int MAXA = 3e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi sieve(MAXA + 1);
  iota(all(sieve), 0);
  for (int i = 2; i * i <= MAXA; i++) {
    if (sieve[i] != i) continue;
    for (int j = i * i; j <= MAXA; j += i) {
      chmin(sieve[j], i);
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, X;
    cin >> N >> X;

    vi A(N);
    for (auto &e : A) cin >> e;

    map<int, int> counts;
    for (int i = X; i != 1; i /= sieve[i]) {
      counts[sieve[i]] = 0;
    }

    for (auto e : A) {
      set<int> primes;
      for (int i = e; i != 1; i /= sieve[i]) {
        primes.insert(sieve[i]);
      }
      for (auto e2 : primes) {
        if (!counts.contains(e2)) continue;
        counts[e2] += e;
      }
    }
    int ans = 0;
    for (auto [e, count] : counts) {
      chmax(ans, count);
    }
    cout << ans << '\n';
  }
}
