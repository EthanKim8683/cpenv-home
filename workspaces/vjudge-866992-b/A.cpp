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

  // always pick max possible
  //
  // K <= M
  //
  // ceil(sum / K) rounds
  //
  // use up rounds
  //
  // fill up rounds further along first

  int T;
  cin >> T;

  while (T--) {
    int N, M, K;
    cin >> N >> M >> K;

    vi A(M);
    for (auto &e : A) cin >> e;

    if (K > M) {
      cout << "NO\n";
      continue;
    }

    int sum = accumulate(all(A), 0ll);
    map<int, int, greater<>> counts;
    counts[0] = 0;
    counts[K] = sum / K;
    if (sum % K > 0) {
      counts[sum % K] = 1;
    }
    bool ok = true;
    for (auto e : A) {
      map<int, int> adds;
      while (e > 0) {
        auto &[x, count] = *counts.begin();
        if (x == 0) {
          ok = false;
          goto SKIP;
        }
        if (e >= count) {
          e -= count;
          adds[x - 1] += count;
          count -= count;
          counts.erase(counts.begin());
        } else {
          count -= e;
          adds[x - 1] += e;
          e -= e;
        }
      }
      for (auto [x, add] : adds) {
        counts[x] += add;
      }
    }
    ok = ok and counts[0] == (sum - 1) / K + 1;
  SKIP:
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
