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

const int LOGM = 18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi counts(M + 1, 0);
    for (auto e : A) {
      counts[e] += 1;
    }

    vi ps(M + 2, 0);
    rep(i, 1, M + 1) { ps[i + 1] = ps[i] + counts[i]; }

    rep(k, 1, min(LOGM, M + 1)) {
      int best = 0;
      rep(s, 1, M + 1) {
        int sum = 0;
        rep(j, 0, min(1ll << k, M / s + 1)) {
          int l = min(j * s, M + 1), r = min((j + 1) * s, M + 1);
          sum += j * (ps[r] - ps[l]);
        }
        rep(j, min(1ll << k, M / s + 1), M / s + 1) {
          int l = min(j * s, M + 1), r = min((j + 1) * s, M + 1);
          sum += ((1ll << k) - 1) * (ps[r] - ps[l]);
        }
        int j = (1ll << k) * s;
        if (j <= M) {
          sum += counts[j];
        }
        chmax(best, sum);
      }
      cout << best << ' ';
    }
    int sum = accumulate(all(A), 0ll);
    rep(k, min(LOGM, M + 1), M + 1) { cout << sum << ' '; }
    cout << '\n';
  }
}
