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
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    if (N % 2 == 0) {
      vc<vi> by_parity(2);
      rep(i, 0, N) { by_parity[i % 2].pb(A[i]); }

      int min0 = min_element(all(by_parity[0])) - by_parity[0].begin(),
          min1 = min_element(all(by_parity[1])) - by_parity[1].begin();
      if (by_parity[0][min0] < by_parity[1][min1]) {
        cout << "Joe\n";
      } else if (by_parity[0][min0] > by_parity[1][min1]) {
        cout << "Mike\n";
      } else {
        if (min0 > min1) {
          cout << "Mike\n";
        } else {
          cout << "Joe\n";
        }
      }
    } else {
      cout << "Mike\n";
    }
  }
}
