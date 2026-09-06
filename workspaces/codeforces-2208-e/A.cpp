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
const int MAXN = 5000;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // 0's split groups
  //
  // then 1st number split groups
  //
  // repeat recursively
  //
  // i think we can do FFT as expected and to handle the predefined X's, we
  // can just set them to 0 if invalid
  //
  // actually i don't think FFT will work because we're not really doing a
  // convolution

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi X(N);
    for (auto &e : X) {
      cin >> e;
      e--;
    }

    // vc dp(N + 1, vi(N + 1, -1));
    // auto dfs = [&](auto self, int l, int r) -> int {
    // 	if (r - l == 0) return 1;
    // 	if (dp[l][r] != -1) return dp[l][r];

    // 	dp[l][r] = 0;
    // 	rep(i, l, r) {
    // 		if (X[i] != -2 and X[i] != l - 1) continue;
    // 		(dp[l][r] += self(self, l, i) * self(self, i + 1, r)) %= MOD;
    // 	}
    // 	return dp[l][r];
    // };
    // cout << dfs(dfs, 0, N) << '\n';

    vc<pii> ranges;
    rep(i, 0, N) {
      if (X[i] == -2) continue;
      ranges.eb(i, X[i]);
    }
    ranges.eb(N, -1);

    auto is_inside = [&](pii a, pii b) -> bool {
      auto [r1, l1] = a;
      auto [r2, l2] = b;
      return l1 <= l2 and r2 < r1;
    };

    auto is_disjoint = [&](pii a, pii b) -> bool {
      auto [r1, l1] = a;
      auto [r2, l2] = b;
      return r1 <= l2 or r2 <= l1;
    };

    bool ok = true;
    for (auto [r, l] : ranges) {
      ok = ok and l < r;
    }
    for (auto a : ranges) {
      for (auto b : ranges) {
        if (a == b) continue;
        ok = ok and (is_inside(a, b) or is_inside(b, a) or is_disjoint(a, b));
      }
    }
    if (!ok) {
      cout << "0\n";
      continue;
    }

    int ans = 1;
    sort(all(ranges));
    for (auto a : ranges) {
      vc<pii> stack;
      for (auto b : ranges) {
        if (a == b) continue;
        if (!is_inside(a, b)) continue;
        while (sz(stack) > 0 and is_inside(b, stack.back())) {
          stack.pop_back();
        }
        stack.pb(b);
      }

      vc<bool> ops;
      int t = a.sd;
      ops.pb(false);
      t++;
      for (auto [r, l] : stack) {
        while (t <= l) {
          ops.pb(true);
          t++;
        }
        t = r;
        ops.pb(false);
        t++;
      }
      while (t < a.fs) {
        ops.pb(true);
        t++;
      }

      vc dp(sz(ops) + 1, vi(sz(ops) + 1, 0));
      dp[0][0] = 1;
      rep(i, 0, sz(ops)) {
        if (ops[i]) {
          int ps = 0;
          for (int j = i; j >= 1; j--) {
            (ps += dp[i][j]) %= MOD;
            (dp[i + 1][j + 1] += ps) %= MOD;
          }
        } else {
          rep(j, 0, i + 1) { (dp[i + 1][j + 1] += dp[i][j]) %= MOD; }
        }
      }
      (ans *= accumulate(all(dp[sz(ops)]), 0ll) % MOD) %= MOD;
    }
    cout << ans << '\n';
  }
}
