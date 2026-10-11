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

const int MAXN = 1e6;
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
    int N;
    cin >> N;

    vi A(N - 1);
    for (auto &e : A) cin >> e;

    int Amax = *max_element(all(A));

    int count = 0;
    auto solve = [&](int split) -> int {
      if (count > 2) return 0;
      count++;

      vc<pair<int, int>> ranges;
      for (int i = split; i - 1 >= 0; i--) {
        if (A[i] < A[i - 1]) return 0;
        if (A[i] == A[i - 1]) {
          ranges.eb(A[i], 1);
        } else {
          ranges.eb(A[i], 0);
        }
      }
      if (split >= 0) {
        ranges.eb(A[0], 0);
      }
      for (int i = split + 1; i + 1 < N - 1; i++) {
        if (A[i] < A[i + 1]) return 0;
        if (A[i] == A[i + 1]) {
          ranges.eb(A[i], 1);
        } else {
          ranges.eb(A[i], 0);
        }
      }
      if (split + 1 <= N - 2) {
        ranges.eb(A[N - 2], 0);
      }
      ranges.eb(N, 0);
      sort(all(ranges));

      vc<bool> used(N + 1, false);
      int n, rv = 1;
      rep(i, 0, sz(ranges)) {
        auto [x, t] = ranges[i];
        if (t == 0) {
          if (used[x]) return 0;
          used[x] = true;
          n = x;
        } else {
          (rv *= n - i) %= MOD;
        }
      }
      return rv;
    };
    int ans = 0;
    rep(i, 0, N - 2) {
      if (A[i] != A[i + 1] and max(A[i], A[i + 1]) == Amax) {
        (ans += solve(i)) %= MOD;
      }
    }
    if (A[0] == Amax) {
      (ans += solve(-1)) %= MOD;
    }
    if (A[N - 2] == Amax) {
      (ans += solve(N - 2)) %= MOD;
    }
    cout << ans << '\n';
  }
}
