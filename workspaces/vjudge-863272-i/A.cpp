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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // split into K parts
  //
  // (N, K, Z) -> (ceil((N - p) / K), K - 1, Z - 1)
  // or
  // (N, K, Z) -> (p, K, Z - 1)
  //
  // flip the problem. largest N we can get for K and Z
  //
  // f(K, Z - 1) + 2 ** K * f(K - 1, Z - 1)

  int N, C, T;
  cin >> N >> C >> T;

  if (N == 1) {
    cout << "0\n";
    exit(0);
  }

  int Z = T / C;
  if (Z == 0) {
    cout << "-1\n";
    exit(0);
  }

  map<pii, int> memo;
  auto f = [&](auto self, int k, int z) -> int {
    if (z == 1) return min(1ll << k, N);
    if (z > k and (1ll << k) >= N) return N;
    if (memo.contains({k, z})) return memo[{k, z}];
    return memo[{k, z}] =
               min(self(self, k, z - 1) +
                       (__int128) (1ll << k) * self(self, k - 1, z - 1),
                   (__int128) N);
  };
  int l = 0, r = __lg(N) + 1;
  while (l < r) {
    int m = l + (r - l) / 2;
    f(f, m, Z) >= N ? r = m : l = m + 1;
  }
  cout << l << '\n';
}
