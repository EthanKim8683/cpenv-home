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

    map<int, int> counts;
    for (auto e : A) {
      counts[e] += 1;
    }

    vi A2;
    int xp = 0;
    for (auto [x, count] : counts) {
      if (x != 0) {
        A2.pb(x - xp);
      }
      A2.pb(count);
      xp = x;
    }
    int count = 0;
    rep(i, 0, sz(A2) - 1) {
      if (A2[i] != 1) break;
      count++;
    }
    cout << (count % 2 == 1 ? "Bob" : "Alice") << '\n';
  }
}
