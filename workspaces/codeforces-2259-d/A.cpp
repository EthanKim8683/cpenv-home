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
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    map<int, vi> indices;
    rep(i, 0, N) { indices[A[i]].pb(i); }

    vi ans(N);
    int xprev = -1;
    bool ok = true, waste = false;
    for (auto [x, indicesx] : indices) {
      if (x > xprev + 1) {
        waste = true;
      } else if (sz(indicesx) < 3) {
        if (x == 0 and sz(indicesx) == 1) {
          ok = false;
          break;
        }
        rep(j, 0, sz(indicesx)) { ans[indicesx[j]] = j; }
        waste = true;
        continue;
      }
      if (waste) {
        for (auto e : indices[x]) {
          ans[e] = 2;
        }
      } else {
        rep(j, 0, sz(indicesx)) { ans[indicesx[j]] = min(j, 2ll); }
      }
      xprev = x;
    }
    if (!ok) {
      cout << "NO\n";
      continue;
    }
    cout << "YES\n";
    for (auto e : ans) {
      cout << "ABC"[e];
    }
    cout << '\n';
  }
}
