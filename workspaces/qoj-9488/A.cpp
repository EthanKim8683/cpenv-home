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

  int N, M, K;
  cin >> N >> M >> K;

  // i remember you said it was based on one of my ideas so i looked towards the
  // (path-1, path) idea
  //
  // and i can imagine, to get to path+1, it's (path-1)*(deg[end of path-1]-1)
  // to exclude? and path we just extend normally...
  //
  // i mean i feel the first paragraph is public knowledge? pendy also knows
  // about the (p-1, p) construction since he helped with formula ig

  vc<pii> edges(M);
  for (auto &[u, v] : edges) {
    cin >> u >> v;
    u--, v--;
  }

  vi deg(N, 0);
  for (auto [u, v] : edges) {
    deg[u] += 1;
    deg[v] += 1;
  }

  vc A(2 * N, vi(2 * N, 0));
  for (auto [u, v] : edges) {
    (A[u][v] += 1) %= MOD;
    (A[v][u] += 1) %= MOD;
  }
  rep(i, 0, N) {
    (A[i][N + i] += 1) %= MOD;
    (A[N + i][i] += MOD - max(deg[i] - 1, 0ll)) %= MOD;
  }

  vc<vi> adj(N);
  for (auto [u, v] : edges) {
    adj[u].pb(v);
    adj[v].pb(u);
  }

  vc x(1, vi(2 * N, 0));
  auto dfs = [&](auto self, int a, int p, int d) -> void {
    if (d > 2) return;
    if (d == 1) {
      x[0][N + a] += 1;
    }
    if (d == 2) {
      x[0][a] += 1;
    }
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a, d + 1);
    }
  };
  dfs(dfs, 0, -1, 0);

  cout << matmul(x, matpow(A, K - 1))[0][N + N - 1] << '\n';
}
