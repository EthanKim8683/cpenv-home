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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    sort(all(A));
    reverse(all(A));

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

    int prod = 1;
    rep(i, 1, N) { (prod *= i) %= MOD; }

    int ans = 0, sum = 0;
    rep(i, 0, N) {
      if (i >= 1) {
        (ans += prod * mod_inv(i) % MOD * (sum - i * A[i] % MOD)) %= MOD;
      }
      (sum += A[i]) %= MOD;
    }
    (ans += MOD) %= MOD;
    cout << ans << '\n';
  }
}
