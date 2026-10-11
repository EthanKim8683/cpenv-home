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

    int lg = __lg(N);
    vi A = {0};
    rep(i, 0, lg + 1) {
      vi A2;
      A2.insert(A2.end(), all(A));
      A2.pb(1 << i);
      A2.insert(A2.end(), all(A));
      A = A2;
    }
    cout << sz(A) << '\n';
    for (auto e : A) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
