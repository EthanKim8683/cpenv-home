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

const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, K;
  cin >> N >> K;

  vi A(N);
  for (auto &e : A) cin >> e;
  sort(all(A));

  map<int, array<int, 3>> counts;
  for (auto e : A) {
    counts[e][2] += 1;
  }
  int sum = 0;
  rep(i, 0, K) {
    sum -= A[i];
    counts[A[i]][0] += 1;
    sum += A[N - 1 - i];
    counts[A[N - 1 - i]][1] += 1;
  }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
      if (y & 1) (rv *= x) %= MOD;
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  vi fact(N + 1);
  fact[0] = 1;
  rep(i, 1, N + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int ans = 1;
  for (auto [x, countsx] : counts) {
    int n = countsx[2], k1 = countsx[0], k2 = countsx[1], k3 = n - k1 - k2;
    (ans *= fact[n] * mod_inv(fact[k1]) % MOD * mod_inv(fact[k2]) % MOD *
            mod_inv(fact[k3]) % MOD) %= MOD;
  }
  if (sum == 0) {
    (ans *= mod_inv(2)) %= MOD;
  }
  cout << sum << ' ' << ans << '\n';
}
