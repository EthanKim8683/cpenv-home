#include <iostream>
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

const int MOD = 998244353;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // add with carry
  //
  // imagine the number x made by going from root to a node, appending each
  // node's value bit by bit. for a node, the final value after time t is the
  // dth bit of x + t, where d is the depth of the node (0 indexed).
  //
  // so basically, the value alternates every 1 << d, and it first flips after t
  // = (1 << d) - x. for each depth, we can narrow down "good" ranges in the
  // period of the depth's values. also period is 2 * (1 << d).
  //
  // for each depth, we only care abt the max and min shift.
  //
  // the leaves are very informative
  //
  // they basically pinpoint the exact t mod some period that the answer must be
  // basically everything has to satisfy this for there to be an answer
  //
  // if all leaves are can be satisfied together, pick the leaf with the
  // greatest period

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    string X;
    cin >> X;

    string Y;
    cin >> Y;

    vi par(N), depth(N);
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      par[a] = p;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
    };
    dfs(dfs, 0, -1, 0);

    pii deepest = {0, 0};
    rep(i, 0, N) { chmax(deepest, pii{depth[i], i}); }

    vi path;
    for (int a = deepest.sd; a != -1; a = par[a]) {
      path.pb(a);
    }
    reverse(all(path));
    vi bits;
    int c = 0;
    for (auto e : path) {
      int x = X[e] - '0', b = ((x + c) & 1) ^ (Y[e] - '0');
      bits.pb(b);
      int sum = x + c + b;
      tie(x, c) = pair{sum % 2, sum / 2};
    }

    auto dfs2 = [&](auto self, int a, int p, int d, int c) -> bool {
      int x = X[a] - '0', sum = x + bits[d] + c;
      tie(x, c) = pair{sum % 2, sum / 2};
      if (x != Y[a] - '0') return false;
      for (auto b : adj[a]) {
        if (b == p) continue;
        if (!self(self, b, a, d + 1, c)) return false;
      }
      return true;
    };
    if (!dfs2(dfs2, 0, -1, 0, 0)) {
      cout << "-1\n";
      continue;
    }

    int ans = 0, pow = 1;
    rep(i, 0, sz(bits)) {
      (ans += pow * bits[i]) %= MOD;
      (pow *= 2) %= MOD;
    }
    cout << ans << '\n';
  }
}
