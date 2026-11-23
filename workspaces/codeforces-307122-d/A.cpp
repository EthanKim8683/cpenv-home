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

  int N, K, S;
  cin >> N >> K >> S;

  int lb = K, ub = K * (N - 1);
  if (!(lb <= S and S <= ub)) {
    cout << "NO\n";
    exit(0);
  }

  if (N == 2) {
    cout << "YES\n";
    rep(i, 0, K) { cout << 2 - i % 2 << ' '; }
    cerr << '\n';
    exit(0);
  }

  int d = (S - K) / (N - 2), r = (S - K) % (N - 2);
  vi dists;
  rep(i, 0, d) { dists.pb(N - 1); }
  if (r > 0) {
    dists.pb(1 + r);
  }
  while (sz(dists) < K) {
    dists.pb(1);
  }

  cout << "YES\n";
  int x = 0;
  for (auto e : dists) {
    if (x + e < N) {
      x += e;
    } else {
      x -= e;
    }
    cout << x + 1 << ' ';
  }
  cout << '\n';
}
