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

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    int sum = 0;
    rep(i, 1, N + 1) { sum ^= i; }
    vi ans(N + 1, 0);
    for (int i = __lg(N) + 1; i >= 1; i--) {
      if (sum >> i & 1) continue;
      int j = 1 << (i - 1);
      assert(ans[j] == 0);
      ans[j] = 1;
      sum ^= j << 1 ^ j;
    }
    // cerr << sum << '\n';
    rep(i, 1, N + 1) { cout << ans[i] << ' '; }
    cout << '\n';
  }
}
