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
    char C;
    cin >> N >> C;

    string S;
    cin >> S;

    int ans = 0;
    for (int l = 0, r = N - 1; l < r; l++, r--) {
      if (S[l] == S[r]) continue;
      if (S[l] == C or S[r] == C) {
        ans += 1;
      } else {
        ans += 2;
      }
    }
    cout << ans << '\n';
  }
}
