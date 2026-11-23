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
    int N, X, S;
    cin >> N >> X >> S;

    string U;
    cin >> U;

    map<int, int> E;
    rep(i, 0, N) {
      if (U[i] != 'I') {
        E.emplace(i, 1);
      }
    }

    int sum = 0;
    map<int, int> I;
    vi leader(N);
    rep(i, 0, N) {
      if (U[i] == 'I') {
        if (sz(I) == X) break;
        auto it = E.upper_bound(i);
        int n = 0;
        for (; it != E.end() and n < S - 1; n++, it = E.erase(it));
        I.emplace(i, n);
        sum += 1 + n;
      }
    }
    int a = 0, ans = sum;
    rep(i, 0, N) {
      if (U[i] == 'A') {
        if (a == X) break;
        if (a + sz(I) == X) {
          auto [j, n] = *I.rbegin();
          if (!(i < j)) break;
          E.emplace(j, n);
          I.erase(j);
          sum -= 1 + n;
        }
        auto it = E.upper_bound(i);
        int nmax = S - 1;
        if (!E.contains(i)) {
          if (it == E.end()) break;
          sum -= 1;
          nmax += 1;
        }
        int n = 0;
        while (it != E.end() and n < nmax) {
          auto &[j, m] = *it;
          int k = min(nmax - n, m);
          n += k;
          m -= k;
          if (m == 0) {
            it = E.erase(it);
          }
        }
        a += 1;
        sum += 1 + n;
        chmax(ans, sum);
      }
    }
    cout << ans << '\n';
  }
}
