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

  int N, Q;
  cin >> N >> Q;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi ps(N + 1);
  ps[0] = 0;
  rep(i, 0, N) { ps[i + 1] = ps[i] + (A[i] == -1 ? 1 : 0); }

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

  vi fact(2 * N + 1);
  fact[0] = 1;
  rep(i, 1, 2 * N + 1) { fact[i] = fact[i - 1] * i % MOD; }

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or k < 0 or n - k < 0) return 0;
    return fact[n] * mod_inv(fact[n - k] * fact[k]) % MOD;
  };

  vi pmin(N + 1);
  pmin[0] = N;
  rep(i, 0, N) { pmin[i + 1] = min(pmin[i], A[i] == -1 ? N : A[i]); }

  vi smin(N + 1);
  smin[N] = N;
  for (int i = N - 1; i >= 0; i--) {
    smin[i] = min(smin[i + 1], A[i] == -1 ? N : A[i]);
  }

  vc<bool> seen(N + 2);
  for (auto e : A) {
    if (e == -1) continue;
    seen[e] = true;
  }

  int n = count(all(A), -1);

  vc ps2(N + 1, vi(N + 2));
  rep(i, 0, N + 1) {
    int m = 0;
    rep(j, 0, N + 1) {
      if (!seen[j]) {
        m += 1;
      }
      ps2[i][j + 1] = (ps2[i][j] + binom(n - m, i - m)) % MOD;
    }
  }

  while (Q--) {
    int l, r;
    cin >> l >> r;
    l--;

    int ex = min(pmin[l], smin[r]), k = ps[r] - ps[l];

    int ans = ps2[k][ex];
    (ans *= fact[k]) %= MOD;
    (ans *= fact[n - k]) %= MOD;
    (ans += MOD) %= MOD;
    cout << ans << '\n';
  }
}
