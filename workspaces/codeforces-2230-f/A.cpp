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

const int LOGQ = 17;
const int INF = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int Q;
  cin >> Q;

  vi V(Q);
  for (auto &e : V) {
    cin >> e;
    e--;
  }

  int N = Q + 1;

  vc<vc<pii>> adj(N);
  rep(i, 0, Q) {
    int a = V[i], b = i + 1;
    pii e1 = {b, sz(adj[b])}, e2 = {a, sz(adj[a])};
    adj[a].pb(e1);
    adj[b].pb(e2);
  }

  vi ans(Q, 1);
  vc<vi> dp(N);
  rep(a, 0, N) {
    dp[a].resize(sz(adj[a]));
    rep(i, 0, sz(adj[a])) { dp[a][i] = adj[a][i].fs; }
  }
  rep(i, 1, LOGQ) {
    vc<vi> dp2(N);
    rep(a, 0, N) { dp2[a].resize(sz(adj[a]), INF); }

    rep(a, 0, N) {
      int d = sz(adj[a]);

      vc ldp(d + 1, vi(2 + 1, INF));
      ldp[0][0] = -INF;
      rep(j, 0, d) {
        rep(k, 0, 2 + 1) {
          chmin(ldp[j + 1][k], ldp[j][k]);
          if (k + 1 <= 2) {
            chmin(ldp[j + 1][k + 1], max(ldp[j][k], dp[a][j]));
          }
        }
      }

      vc rdp(d + 1, vi(2 + 1, INF));
      rdp[d][0] = -INF;
      for (int j = d - 1; j >= 0; j--) {
        rep(k, 0, 2 + 1) {
          chmin(rdp[j][k], rdp[j + 1][k]);
          if (k + 1 <= 2) {
            chmin(rdp[j][k + 1], max(rdp[j + 1][k], dp[a][j]));
          }
        }
      }

      rep(j, 0, d) {
        auto [b, k] = adj[a][j];
        rep(l, 0, 2 + 1) {
          chmin(dp2[b][k], max(a, max(ldp[j][l], rdp[j + 1][2 - l])));
        }
      }

      if (ldp[d][2] != INF) {
        chmax(ans[max(max(a, ldp[d][2]) - 1, 0ll)], i + 1);
      }
    }

    dp = dp2;
  }
  rep(i, 0, Q - 1) { chmax(ans[i + 1], ans[i]); }
  for (auto e : ans) {
    cout << e << ' ';
  }
}
