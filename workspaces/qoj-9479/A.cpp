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
const int LOGM = 30;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

vc<vi> matmul(vc<vi> a, vc<vi> b) {
  vc rv(sz(a), vi(sz(b[0]), 0));
  rep(i, 0, sz(a)) rep(j, 0, sz(b[0])) rep(k, 0, sz(a[0])) {
    (rv[i][j] += a[i][k] * b[k][j]) %= MOD;
  }
  return rv;
}

vc<vi> matpow(vc<vi> x, int y) {
  vc rv(sz(x), vi(sz(x), 0));
  rep(i, 0, sz(x)) rv[i][i] = 1;
  for (; y; y >>= 1, x = matmul(x, x))
    if (y & 1) rv = matmul(rv, x);
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, M;
  cin >> N >> M;

  vc x(4, vi(4, 0));
  x[0][3] = 1;
  x[1][2] = 1;
  x[2][3] = 1;
  x[3][0] = 1;
  x[3][1] = 1;
  x = matpow(x, N);

  vi w(3, 0);
  w[0] = 1;
  w[1] = 0;
  rep(i, 0, 4) { (w[1] += x[i][i]) %= MOD; }
  w[2] = 1;

  vc dp(LOGM + 1, vi(2, 0));
  dp[0][0] = 1;
  rep(i, 0, LOGM) {
    rep(j, 0, 2) {
      rep(k, 0, 3) {
        if ((j + k) % 2 != (M >> i & 1)) continue;
        (dp[i + 1][(j + k) / 2] += dp[i][j] * w[k]) %= MOD;
      }
    }
  }
  cout << dp[LOGM][0] << '\n';
}
