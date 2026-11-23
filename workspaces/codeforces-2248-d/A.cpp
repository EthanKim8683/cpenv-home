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

    string S;
    cin >> S;

    string T;
    cin >> T;

    vi masks(N);
    rep(i, 0, N) { masks[i] = (S[i] - '0') << 1 | (T[i] - '0'); }

    vc ps(4, vi(N + 1, 0));
    rep(i, 0, N) { ps[masks[i]][i + 1] = 1; }
    rep(i, 0, 4) {
      rep(j, 0, N) { ps[i][j + 1] += ps[i][j]; }
    }

    while (Q--) {
      int l, r;
      cin >> l >> r;
      l--;

      vi counts(4, 0);
      rep(i, 0, 4) { counts[i] = ps[i][r] - ps[i][l]; }

      int d1 = abs(counts[1] - counts[2]), d2 = abs(counts[0] - counts[3]),
          d3 = min(counts[0], counts[3]);
      d1 -= d3;
      d2 += d3;
      cout << (d1 <= d2 ? "YES" : "NO") << '\n';
    }
  }
}
