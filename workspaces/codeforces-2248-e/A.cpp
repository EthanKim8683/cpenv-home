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

  int T;
  cin >> T;

  while (T--) {
    int N, M, D;
    cin >> N >> M >> D;

    vc<pii> pr(M);
    for (auto &[p, r] : pr) {
      cin >> p >> r;
    }

    int rsum = 0;
    for (auto [p, r] : pr) {
      rsum += r;
    }

    bool found = false;
    int raccum = 0;
    rep(i, 0, M) {
      auto [p, r] = pr[i];
      raccum += r;
      if ((__int128) N * (D * p + raccum) > (__int128) p * (D * N + rsum)) {
        found = true;
      }
    }
    cout << (found ? "YES" : "NO") << '\n';
  }
}
