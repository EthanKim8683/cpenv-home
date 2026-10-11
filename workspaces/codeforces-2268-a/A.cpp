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
    K--;

    vi A(N);
    for (auto &e : A) cin >> e;

    int ans = 0;
    if (N > 2 * K + 1) {
      rep(i, K, N - K) { ans += A[i]; }
      rep(i, 0, K) { ans += max(A[i], A[N - 1 - i]); }
    } else {
      rep(i, 0, N - K) { ans += max(A[i], A[N - 1 - i]); }
    }
    cout << ans << '\n';
  }
}
