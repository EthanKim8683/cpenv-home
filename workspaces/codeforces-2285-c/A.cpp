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

const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int a, int b, int m = MOD) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    map<int, int, greater<int>> counts;
    for (auto e : A) {
      counts[e] += 1;
    }
    int ge = 0, ans = 1;
    for (auto [x, n] : counts) {
      if (n > 1) break;
      ge += n;
      (ans += mod_pow(x - 1, ge)) %= MOD;
    }
    cout << ans << '\n';
  }
}
