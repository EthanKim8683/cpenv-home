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

const int LOGM = 17;

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

    string S;
    cin >> S;

    vc<vi> adj;
    vi stack;
    stack.pb(sz(adj));
    adj.eb();
    for (auto e : S) {
      if (e == '(') {
        adj[stack.back()].pb(sz(adj));
        stack.pb(sz(adj));
        adj.eb();
      } else {
        stack.pop_back();
      }
    }

    int M = sz(adj);

    vc anc(M, vc<pii>(LOGM + 1));
    anc[0][0] = {0, K + 1};
    auto dfs = [&](auto self, int a) -> int {
      int l = 0;
      for (auto b : adj[a]) {
        int n = self(self, b);
        anc[b][0] = {a, l};
        l += n;
      }
      return 1 + l;
    };
    dfs(dfs, 0);

    rep(i, 1, LOGM + 1) {
      rep(j, 0, M) {
        auto [p1, d1] = anc[j][i - 1];
        auto [p2, d2] = anc[p1][i - 1];
        anc[j][i] = {p2, d1 + d2};
      }
    }

    int ans = 0;
    rep(i, 0, M) {
      int a = i, d = 0, n = 1;
      for (int j = LOGM; j >= 0; j--) {
        auto [p, d2] = anc[a][j];
        if (d + d2 <= K) {
          a = p;
          d += d2;
          n += 1ll << j;
        }
      }
      if (a == 0) {
        n = min(n + K - 1, N / 2);
      }
      chmax(ans, n);
    }
    cout << ans << '\n';
  }
}
