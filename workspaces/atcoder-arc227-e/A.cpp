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

  int N, M;
  cin >> N >> M;

  vi A(M);
  for (auto &e : A) cin >> e;
  sort(all(A));
  A.erase(unique(all(A)), A.end());

  if (N <= 20 and M <= 10) {
    set<int> S;
    auto dfs = [&](auto self, int x) -> void {
      if (S.contains(x)) return;
      S.insert(x);
      for (auto e : A) {
        self(self, x ^ x << e);
      }
    };
    dfs(dfs, 1);
    cerr << sz(S) << '\n';
  }

  auto f = [&](int x, int n) -> int {
    return 1ll << __lg(2 * ((n - 1) / x + 1) - 1);
  };

  vc<bool> seen(N, false);
  int ans = 1;
  for (auto e : A) {
    int n = N;
    for (int i = e; i < N; i *= 2) {
      if (seen[i]) {
        chmin(n, i);
      } else {
        seen[i] = true;
      }
    }
    cerr << e << ": " << n << ", " << f(e, n) << '\n';
    (ans *= f(e, n)) %= MOD;
  }
  cout << ans << '\n';
}
