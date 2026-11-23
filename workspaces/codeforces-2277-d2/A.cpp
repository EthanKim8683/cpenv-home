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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int L, R;
    cin >> L >> R;

    auto f = [&](auto self, int x) -> int {
      if (x == 0) return 0;
      if (x == 1) return 1;
      if (x == 2) return 3;
      if (x == 3) return 2;
      int k = __lg(x);
      return min(k + 1 + self(self, (x + 1) - ((1ll << k) - 1)),
                 (k + 1) + ((1ll << (k + 1)) - 1 - x));
    };
    int ans = 0;
    rep(i, L, R + 1) { (ans += f(f, i)) %= MOD; }
    cout << ans << '\n';
  }
}
