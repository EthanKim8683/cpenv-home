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
    string S;
    cin >> S;

    int N = sz(S);

    vc memo1(N + 1, vi(N + 1, -1));
    vc memo2(N + 1, vc(N + 1, vi(2, -1)));
    function<int(int, int)> dfs1;
    function<int(int, int, int)> dfs2;
    dfs1 = [&](int l, int r) -> int {
      auto &rv = memo1[l][r];
      if (rv != -1) return rv;

      if (r - l == 0) {
        rv = 1;
        return rv;
      }

      rv = min(dfs2(l + 1, r, 0), dfs2(l, r - 1, 1));
      return rv;
    };
    dfs2 = [&](int l, int r, int p) -> int {
      auto &rv = memo2[l][r][p];
      if (rv != -1) return rv;

      char c;
      if (p == 0) {
        c = S[l - 1];
      } else {
        c = S[r];
      }

      int rv1 = dfs1(l + 1, r), rv2 = dfs1(l, r - 1);
      if (rv1 == 1) {
        if (S[l] > c) {
          rv1 = 0;
        } else if (S[l] < c) {
          rv1 = 2;
        }
      }
      if (rv2 == 1) {
        if (S[r - 1] > c) {
          rv2 = 0;
        } else if (S[r - 1] < c) {
          rv2 = 2;
        }
      }
      rv = max(rv1, rv2);
      return rv;
    };
    cout << (string[]) {"Alice", "Draw", "Bob"}[dfs1(0, N)] << '\n';
  }
}
