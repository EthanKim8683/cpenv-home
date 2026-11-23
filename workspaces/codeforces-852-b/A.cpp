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

const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, L, M;
  cin >> N >> L >> M;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(N);
  for (auto &e : B) cin >> e;

  vi C(N);
  for (auto &e : C) cin >> e;

  vi counts(M, 0);
  for (auto e : B) {
    counts[e % M] += 1;
  }

  vc mat(M, vi(M, 0));
  rep(i, 0, M) {
    rep(j, 0, M) { mat[i][(i + j) % M] = counts[j]; }
  }

  vc vec(1, vi(M, 0));
  for (auto e : A) {
    vec[0][e % M] += 1;
  }

  vi counts2(M, 0);
  rep(i, 0, N) { counts2[(B[i] + C[i]) % M] += 1; }

  vc mat2(M, vi(M, 0));
  rep(i, 0, M) {
    rep(j, 0, M) { mat2[i][(i + j) % M] = counts2[j]; }
  }

  auto matmul = [&](vc<vi> a, vc<vi> b) -> vc<vi> {
    vc rv(sz(a), vi(sz(b[0]), 0));
    rep(i, 0, sz(a)) rep(j, 0, sz(b[0]))
        rep(k, 0, sz(a[0]))(rv[i][j] += a[i][k] * b[k][j]) %= MOD;
    return rv;
  };

  auto matpow = [&](vc<vi> x, int y) -> vc<vi> {
    vc rv(sz(x), vi(sz(x), 0));
    rep(i, 0, sz(x)) rv[i][i] = 1;
    for (; y; y >>= 1, x = matmul(x, x))
      if (y & 1) rv = matmul(rv, x);
    return rv;
  };

  cout << matmul(vec, matmul(matpow(mat, L - 2), mat2))[0][0] << '\n';
}
