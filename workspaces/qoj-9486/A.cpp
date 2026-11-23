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

const int MAXN = 8000;
const int MAXM = 8000;
const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int x, int y) {
  int rv = 1;
  for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
    if (y & 1) (rv *= x) %= MOD;
  return rv;
}

int mod_inv(int x) { return mod_pow(x, MOD - 2); }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  vi inv_fact(MAXN + 1);
  rep(i, 0, MAXN + 1) { inv_fact[i] = mod_inv(fact[i]); }

  vc s2(MAXN + 1, vi(MAXM + 1, 0));
  s2[0][0] = 1;
  rep(i, 1, MAXN + 1) {
    rep(j, 1, MAXM + 1) {
      s2[i][j] = (j * s2[i - 1][j] + s2[i - 1][j - 1]) % MOD;
    }
  }

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or n - k < 0 or k < 0) return 0;
    return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
  };

  // k! * S2(N, k) * i * binom(M-(i+1), k-i)
  // M! * S2(N, M) * M
  //
  // i * binom(M-(i+1), k-i)
  // binom(i, 1) * binom(M-(i+1), k-i)
  // binom(i, 1) * binom(M-(i+1), M-(i+1)-(k-i))
  // binom(i, 1) * binom(M-(i+1), M-1-k)
  // binom(M, M-k+1)
  //
  // k! * S2(N, k) * binom(M, M-k+1)
  // k! * S2(N, k) * binom(M, k-1)
  //
  // binom(n, k) = binom(n-1, k-1) + binom(n-1, k)
  // binom(n-1, k-1) = binom(n, k) - binom(n-1, k)
  //
  // k! * S2(N, k) * (binom(M+1, k) - binom(M, k))
  // k! * S2(N, k) * ((M+1)!/k!/(M+1-k)! - M!/k!/(M-k)!)
  // S2(N, k) * ((M+1)!/(M+1-k)! - M/(M-k)!)
  // S2(N, k) * (M+1)_k - S2(N, k) * (M)_k
  // (M+1)^N - (M)^N

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    int ans = (mod_pow(M + 1, N) + MOD - mod_pow(M, N)) % MOD;
    if (N > M) {
      (ans += MOD - fact[M + 1] * s2[N][M + 1] % MOD) %= MOD;
    }
    (ans *= mod_inv(mod_pow(M, N))) %= MOD;
    cout << ans << '\n';
  }
}
