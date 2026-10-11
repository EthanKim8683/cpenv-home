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

    vi B(N);
    for (auto &e : B) cin >> e;

    vi ps(N + 1, 0);
    rep(i, 0, N) {
      if (B[i] == -1) continue;
      if (B[i] == 0) continue;
      ps[max(i - B[i] + 1, 0ll)] += 1;
      ps[min(i + B[i], N)] -= 1;
    }
    rep(i, 0, N) { ps[i + 1] += ps[i]; }

    bool ok = true;
    rep(i, 0, N) {
      if (B[i] == -1) continue;
      bool found = false;
      if (i - B[i] >= 0) {
        found = found or ps[i - B[i]] == 0;
      }
      if (i + B[i] < N) {
        found = found or ps[i + B[i]] == 0;
      }
      ok = ok and found;
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }

    rep(i, 0, N) { cout << (ps[i] == 0 ? 1 : 0); }
    cout << '\n';
  }
}
