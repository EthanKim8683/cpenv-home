#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

  int K;
  cin >> K;

  int N = 2 * K + 1;

  vi deg(N, K);
  vc<vi> adj(N);
  auto add_edge = [&](int a, int b) -> void {
    assert(deg[a] >= 1);
    deg[a] -= 1;
    adj[a].pb(b);
  };
  rep(i, 0, N) {
    rep(j, i + 1, min(i + 1 + K, N)) { add_edge(i, j); }
    rep(j, min(i + 1 + K, N), N) { add_edge(j, i); }
  }

  cout << N << '\n';
  for (auto r : adj) {
    assert(sz(r) == K);
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
