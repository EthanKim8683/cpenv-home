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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // we can do matrix exponentiation on the bottom
  //
  // and we multiply by the M - max(b1, b2) to account for the tops
  //
  // i think we must use PIE (and matrix exponentiation, of course)
  //
  // every column picks a side to be invalidated on in the next column, which
  // contributes the amount above and the amount below

  int N, M, MOD;
  cin >> N >> M >> MOD;

  auto matmul = [&](vc<vi> a, vc<vi> b) -> vc<vi> {
    assert(a[0].size() == b.size());
    vc rv(a.size(), vi(b[0].size(), 0));
    rep(i, 0, a.size()) {
      rep(j, 0, b[0].size()) {
        rep(k, 0, a[0].size()) { (rv[i][j] += a[i][k] * b[k][j]) %= MOD; }
      }
    }
    return rv;
  };

  auto matpow = [&](vc<vi> x, int y) -> vc<vi> {
    assert(x.size() == x[0].size());
    vc rv(x.size(), vi(x.size(), 0));
    rep(i, 0, x.size()) { rv[i][i] = 1; }
    for (; y; y >>= 1, x = matmul(x, x)) {
      if (y & 1) {
        rv = matmul(rv, x);
      }
    }
    return rv;
  };

  vc x(M + 2, vi(M + 2, 0));
  rep(i, 0, M) {
    rep(j, 0, i) {
      rep(k, j, i) {
        (x[i][j] -= 1) %= MOD;
        (x[i][M - 1 - k] -= 1) %= MOD;
        (x[i][M] += 1) %= MOD;
        (x[i][M + 1] += 1) %= MOD;
      }
    }
  }
  rep(i, 0, M){rep(j, i, M){(x[M][i] -= 1) %= MOD;
  (x[M][M - 1 - j] -= 1) %= MOD;
  (x[M][M] += 1) %= MOD;
  (x[M][M + 1] += 1) %= MOD;
}
}
(x[M + 1][M + 1] += 1) %= MOD;
auto xpow = matpow(x, N - 1);
int ans = 0;
rep(i, 0, M) {
  (ans -= xpow[M - 1 - i][M + 1]) %= MOD;
  (ans += xpow[M][M + 1]) %= MOD;
  (ans += xpow[M + 1][M + 1]) %= MOD;
}
(ans += MOD) %= MOD;
cout << ans << '\n';
}
