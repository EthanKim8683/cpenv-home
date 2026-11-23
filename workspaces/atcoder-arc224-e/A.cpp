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

  int T;
  cin >> T;

  while (T--) {
    string S;
    cin >> S;

    vc<char> stack;
    int ans = 0;
    for (auto e : S) {
      if (e != 'A') {
        while (sz(stack) > 0 and stack.back() != e - 1) {
          stack.pop_back();
        }
        if (stack.empty()) {
          ans += 1;
          continue;
        }
        stack.pop_back();
      }
      stack.pb(e);
    }
    cout << ans << '\n';
  }
}
