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

  int N;
  cin >> N;

  vi S(N);
  for (auto &e : S) {
    cin >> e;
    e--;
  }

  vi T = S;
  sort(all(T));

  vc<set<pii>> adj(N);
  rep(i, 0, N) {
    if (S[i] == T[i]) continue;
    adj[S[i]].emplace(T[i], i);
  }

  vc<vi> ans;
  vi path;
  auto dfs = [&](auto self, int a) -> void {
    while (sz(adj[a]) > 0) {
      auto [b, i] = *adj[a].begin();
      adj[a].erase(adj[a].begin());
      path.pb(i);
      self(self, b);
    }
  };
  rep(i, 0, N) {
    path.clear();
    dfs(dfs, i);
    if (sz(path) > 0) {
      ans.pb(path);
    }
  }
  cout << sz(ans) << '\n';
  for (auto r : ans) {
    cout << sz(r) << '\n';
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
