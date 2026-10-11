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
const int MAXN = 5e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  vi dp(MAXN + 1);
  dp[1] = 0;
  int sum = dp[1];
  rep(i, 2, MAXN + 1) {
    dp[i] = (i - 1 + sum) % MOD;
    (sum += dp[i]) %= MOD;
  }

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(K);
    for (auto &e : A) cin >> e;

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

    vi stack;
    for (int i = sz(A) - 1; i >= 0; i--) {
      while (sz(stack) > 0 and stack.back() < A[i]) {
        stack.pop_back();
      }
      stack.pb(A[i]);
    }

    vc<bool> seen(N + 1, false);
    for (auto e : stack) {
      seen[e] = true;
    }

    int ans = 0;

    rep(i, 1, stack[0] + 1) {
      if (seen[i]) continue;
      (ans += (1 + dp[i]) * fact[N - K]) %= MOD;
    }

    rep(i, stack[0] + 1, N + 1) {
      (ans += (1 + dp[i]) * binom(N - K, N - i + 1) % MOD * (N - i) % MOD *
              fact[N - i] % MOD * fact[N - K - (N - i + 1)]) %= MOD;
    }

    cout << ans << '\n';

    // int ans = 0;
    // (ans += fact[N - K] * N) %= MOD;
    // cerr << '\t' << ans << '\n';

    // (ans -= fact[N - K] * sz(stack)) %= MOD;
    // (ans += MOD) %= MOD;
    // cerr << '\t' << ans << '\n';

    // int ev = 0;
    // rep(i, 0, gt) { ev += mod_inv(i + 1); }
    // (ans -= binom(N - K, gt) * fact[gt] % MOD * ev) %= MOD;
    // (ans += MOD) %= MOD;
    // cerr << '\t' << ans << '\n';

    // rep(i, 1, gt) {
    //   int b = N - i;
    //   (ans += b * (b - 1) / 2 % MOD * i % MOD * binom(N - K, i + 1) % MOD *
    //           fact[N - K - (i + 1)]) %= MOD;
    // }
    // cerr << '\t' << ans << '\n';

    // vc<bool> seen(N + 1, false);
    // for (auto e : A) {
    //   seen[e] = true;
    // }
    // int Amax = 0, b = 0;
    // for (auto e : A) {
    //   if (e < Amax) {
    //     chmax(b, e);
    //   }
    //   chmax(Amax, e);
    // }
    // rep(i, 1, Amax) {
    //   if (seen[i]) continue;
    //   chmax(b, i);
    // }
    // (ans +=
    //  b * (b - 1) / 2 % MOD * binom(N - K, gt) % MOD * fact[N - K - gt]) %=
    //  MOD;
    // cerr << '\t' << ans << '\n';

    // cout << ans << '\n';
  }
}
