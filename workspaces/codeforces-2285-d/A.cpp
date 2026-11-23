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

const int MAXN = 2e5;
const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int a, int b, int m = MOD) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}

int mod_inv(int a, int m = MOD) { return mod_pow(a, m - 2); }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) fact[i] = fact[i - 1] * i % MOD;

  vi inv_fact(MAXN + 1);
  rep(i, 0, MAXN + 1) inv_fact[i] = mod_inv(fact[i]);

  auto binom = [&](int n, int k) -> int {
    if (n < 0 or n - k < 0 or k < 0) return 0;
    return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
  };

  int T;
  cin >> T;

  while (T--) {
    int N, M, Q;
    cin >> N >> M >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps1(N + 1, 0), ps2(N + 1, 0);
    rep(i, 0, N) {
      ps1[i + 1] += A[i];
      ps2[N - i] += A[i];
    }
    rep(i, 0, N) {
      ps1[i + 1] += ps1[i];
      ps2[i + 1] += ps2[i];
    }

    map<int, vi> indices;
    rep(i, 0, N + 1) { indices[ps1[i] - ps2[i]].pb(i); }

    auto count = [&](int x, int l, int r) -> int {
      if (!indices.contains(x)) return 0;
      return lower_bound(all(indices[x]), r) - lower_bound(all(indices[x]), l);
    };

    while (Q--) {
      int i, v;
      cin >> i >> v;
      i--;

      int l = i + 1, r = N - i, n = 0;
      if (l <= r) {
        n += count(0, 0, l);
        n += count(-v, l, r);
        n += count(0, r, N + 1);
      } else {
        swap(l, r);
        n += count(0, 0, l);
        n += count(v, l, r);
        n += count(0, r, N + 1);
      }
      cout << binom(n - 2, M - 1) << '\n';
    }
  }
}
