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

typedef long double ld;

struct State {
  int c0, c2, c3;

  State(int a0, int a2, int a3) : c0(a0), c2(a2), c3(a3) {}
};

map<State, ld> mp;

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;
  vi arr(4, 0);
  rep(i, 0, k + 1) cin >> arr[i];

  if (k == 0) {
    if (n == 1) {
      cout << "1\n";
    } else
      cout << "0\n";
    return 0;
  }

  // maybe need to case-work k=1.
  // we don't even need all.

  int mx_dim = (arr[0] + 1) / 2 + 1;

  // bc. if 500, 500, 500, then the second 500 is equivalent to 250, since otw
  // will fail. we can reduce dim.
  vc<vc<vc<ld>>> dp(2, vc<vc<ld>>(min(arr[2] + 1, arr[0] + 2),
                                  vc<ld>(min(mx_dim, arr[3] + 1), -1)));

  auto get_dp = [&](auto &self, int c0, int c2, int c3) -> void {
    if (dp[c0 % 2][c2][c3] >= 0) return;

    int curtot = c0 + c2 + c3;
    int tot_rem = arr[0] + arr[2] + arr[3] - curtot;

    // determine if is winning state or losing state.
    if (c2 + c3 * 2 - c0 < 0) {
      dp[c0 % 2][c2][c3] = 0;
      return;
    }
    if (c2 + c3 * 2 >= arr[0]) {
      dp[c0 % 2][c2][c3] = 1;
      return;
    }

    ld ret = 0.0;
    // check for all possible future outcomes.
    if (c2 != arr[2]) {
      ld tmp = (1.0L * (arr[2] - c2) / tot_rem);
      self(self, c0, c2 + 1, c3);
      ret += tmp * dp[c0 % 2][c2 + 1][c3];
    }
    if (c3 != arr[3]) {
      ld tmp = (1.0L * (arr[3] - c3) / tot_rem);
      self(self, c0, c2, c3 + 1);
      ret += tmp * dp[c0 % 2][c2][c3 + 1];
    }
    if (c0 != arr[0]) {
      ld tmp = (1.0L * (arr[0] - c0) / tot_rem);
      self(self, c0 + 1, c2, c3);
      ret += tmp * dp[(c0 + 1) % 2][c2][c3];
    }

    dp[c0 % 2][c2][c3] = ret;
  };
  get_dp(get_dp, 0, 0, 0);

  cout << fixed << setprecision(10) << dp[0][0][0] << "\n";

  // int x1, x2, x3; cin >> x1 >> x2 >> x3;
  // get_dp(get_dp, x1, x2, x3);
  // cerr << dp[x1][x2][x3] << '\n';

  return 0;
}
