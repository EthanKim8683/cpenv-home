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

const int MOD = 1e9 + 7;

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

    vi index(N);
    int t = 0;
    rep(i, 0, N) {
      if (ps[i] != 0) continue;
      index[i] = t;
      t++;
    }

    bool ok = true;
    vc<bool> ones(t, false), twos(t, false);
    rep(i, 0, N) {
      if (B[i] == -1) continue;
      if (B[i] == 0) {
        if (ps[i] == 0) {
          ones[index[i]] = true;
        } else {
          ok = false;
          break;
        }
        continue;
      }
      bool left = i - B[i] >= 0 and ps[i - B[i]] == 0,
           right = i + B[i] < N and ps[i + B[i]] == 0;
      if (left and right) {
        twos[index[i + B[i]]] = true;
      } else if (left) {
        ones[index[i - B[i]]] = true;
      } else if (right) {
        ones[index[i + B[i]]] = true;
      } else {
        ok = false;
        break;
      }
    }
    if (!ok) {
      cout << "0\n";
      continue;
    }

    vc dp(t + 1, vc(2, vi(2, 0)));
    dp[0][0][0] = 1;
    rep(i, 0, t) {
      rep(j, 0, 2) {
        rep(k, 0, 2) {
          rep(l, 0, 2) {
            if (ones[i]) {
              if (l == 0) continue;
            }
            if (twos[i]) {
              if (j == 0 and l == 0) continue;
            }
            (dp[i + 1][l][k | l] += dp[i][j][k]) %= MOD;
          }
        }
      }
    }
    cout << (dp[t][0][1] + dp[t][1][1]) % MOD << '\n';
  }
}
