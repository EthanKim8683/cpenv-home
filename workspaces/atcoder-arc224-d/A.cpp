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

const int LOGK = 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    auto binom = [&](int n, int k) -> int {
      int rv = 1;
      rep(i, n - k + 1, n + 1) { rv *= i; }
      rep(i, 1, k + 1) { rv /= i; }
      return rv;
    };

    vi counts(N + 1, 0);
    int sum = 0;
    rep(i, 0, N + 1) {
      if (sum >= K) break;
      int d = min(binom(N, i), K - sum);
      counts[i] += d;
      sum += d;
    }
    if (sum < K) {
      cout << "-1\n";
      continue;
    }

    auto pow = [&](int a, int b) -> int {
      int rv = 1;
      rep(i, 0, b) { rv *= a; }
      return rv;
    };

    vi counts2(LOGK + 1, 0);
    sum = 0;
    rep(i, 1, LOGK + 1) {
      if (sum >= K) break;
      int d = min(9 * pow(10, i - 1), K - sum);
      counts2[i] += d;
      sum += d;
    }

    int ans = 0;
    for (int i = 0, j = LOGK; i <= N and j >= 0;) {
      if (counts[i] == 0) {
        i++;
      } else if (counts2[j] == 0) {
        j--;
      } else {
        int d = min(counts[i], counts2[j]);
        ans += d * i * j;
        counts[i] -= d;
        counts2[j] -= d;
      }
    }
    cout << ans << '\n';
  }
}
