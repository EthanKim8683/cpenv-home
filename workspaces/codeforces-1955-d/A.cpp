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
    int N, M, K;
    cin >> N >> M >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(M);
    for (auto &e : B) cin >> e;

    map<int, int> counts1, counts2;
    int sum = 0;
    auto add1 = [&](int x, int d) -> void {
      sum -= min(counts1[x], counts2[x]);
      counts1[x] += d;
      sum += min(counts1[x], counts2[x]);
    };
    auto add2 = [&](int x, int d) -> void {
      sum -= min(counts1[x], counts2[x]);
      counts2[x] += d;
      sum += min(counts1[x], counts2[x]);
    };
    for (auto e : B) {
      add2(e, 1);
    }
    rep(i, 0, M) { add1(A[i], 1); }
    int ans = 0;
    rep(i, 0, N - M + 1) {
      if (sum >= K) {
        ans++;
      }
      if (i + M >= N) break;
      add1(A[i], -1);
      add1(A[i + M], 1);
    }
    cout << ans << '\n';
  }
}
