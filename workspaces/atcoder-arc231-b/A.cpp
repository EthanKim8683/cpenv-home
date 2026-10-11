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

const int K = 1 << 10;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int A, B, C;
    cin >> A >> B >> C;

    bool ok = true;
    rep(i, 0, A) {
      rep(j, 0, B) { ok = ok and (i ^ j) != C; }
    }
    if (!ok) {
      cout << "No\n";
      continue;
    }

    vi X(A), Y(B);
    iota(all(X), 0);
    iota(all(Y), 0);

    X.pb(K);
    rep(i, 0, C) { Y.pb(i ^ K); }

    cout << "Yes\n";
    cout << sz(X);
    for (auto e : X) {
      cout << ' ' << e;
    }
    cout << '\n';
    cout << sz(Y);
    for (auto e : Y) {
      cout << ' ' << e;
    }
    cout << '\n';
  }
}
