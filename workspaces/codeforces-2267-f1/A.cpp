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
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ans;
    while (count(all(A), 0) != N) {
      ans.pb(*max_element(all(A)) - *min_element(all(A)));
      vi sums;
      rep(i, 0, N) {
        rep(j, i + 1, N) { sums.pb(A[i] ^ A[j]); }
      }
      sort(all(sums));
      A = {sums.begin(), sums.begin() + N};
    }
    while (Q--) {
      int X;
      cin >> X;

      if (X >= sz(ans)) {
        cout << "0\n";
      } else {
        cout << ans[X] << '\n';
      }
    }
  }
}
