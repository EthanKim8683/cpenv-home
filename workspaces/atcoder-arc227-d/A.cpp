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

  int N, M, Q;
  cin >> N >> M >> Q;

  vc<string> S(N);
  for (auto &e : S) cin >> e;

  vc seen(M, vc(2, vc(M, vc<bool>(2, false))));
  for (auto e : S) {
    rep(i, 0, M) {
      rep(j, 0, M) { seen[i][e[i] - '0'][j][e[j] - '0'] = true; }
    }
  }

  while (Q--) {
    string T;
    cin >> T;

    bool ok = true;
    rep(i, 0, M) {
      rep(j, 0, M) { ok = ok and seen[i][T[i] - '0'][j][T[j] - '0']; }
    }
    cout << (ok ? "Yes" : "No") << '\n';
  }
}
