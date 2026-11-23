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

  int N;
  cin >> N;

  vc<string> S(N);
  for (auto &e : S) cin >> e;

  int M;
  cin >> M;

  vc<string> T(M);
  for (auto &e : T) cin >> e;

  set<string> Sset;
  for (auto e : S) {
    e[0] = 'G';
    Sset.insert(e);
  }
  int ans = 0;
  for (auto e : T) {
    if (Sset.contains(e)) {
      ans++;
    }
  }
  cout << ans << '\n';
}
