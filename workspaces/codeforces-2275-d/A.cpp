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

  //

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vc<tuple<int, int, int>> labs(N);
    for (auto &[a, b, c] : labs) {
      cin >> a >> b >> c;
    }

    vi cost_to_inc(N), sum(N);
    rep(i, 0, N) {
      auto [a, b, c] = labs[i];
      if (a > b or b > c) {
        cost_to_inc[i] = 0;
      } else {
        cost_to_inc[i] = 1e18;
        if (b > a) {
          chmin(cost_to_inc[i], c - (max(a, b) - 1));
        }
        if (c > a) {
          chmin(cost_to_inc[i], b - (a - 1));
        }
      }
      sum[i] = a + b + c;
    }

    auto check = [&](int x) -> bool {
      int cost = 0;
      rep(i, 0, N) {
        if (sum[i] < x) {
          cost += 2 * cost_to_inc[i] + x - sum[i];
        }
        if (cost > K) return false;
      }
      return true;
    };
    int l = -3e9, r = 3e9 + 1e18;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      check(m) ? l = m : r = m - 1;
    }
    cout << l << '\n';
  }
}
