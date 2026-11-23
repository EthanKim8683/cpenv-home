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

const int MAXN = 50;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int a, int b, int m) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi primes, phi(MAXN * MAXN + 2), lpf(MAXN * MAXN + 2);
  vc<bool> is_prime(MAXN * MAXN + 2, true);
  phi[1] = 1;
  lpf[1] = 1;
  rep(i, 2, MAXN * MAXN + 2) {
    if (is_prime[i]) {
      primes.pb(i);
      phi[i] = i - 1;
      lpf[i] = i;
    }
    for (auto e : primes) {
      if (i * e > MAXN * MAXN + 1) break;
      is_prime[i * e] = false;
      lpf[i * e] = e;
      if (i % e == 0) {
        phi[i * e] = phi[i] * e;
        break;
      }
      phi[i * e] = phi[i] * phi[e];
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N, R;
    cin >> N >> R;

    if (R == 0) {
      cout << "No\n";
      continue;
    }

    if (N == 1) {
      cout << "Yes\n1\n";
      continue;
    }

    int mod = N * N + 1;

    if (N == 2) {
      if (R == 1 * 2 * 3 * 4 % mod) {
        cout << "Yes\n1 2\n3 4\n";
      } else {
        cout << "No\n";
      }
      continue;
    }

    vi primes;
    for (int i = phi[mod]; i != 1; i /= lpf[i]) {
      primes.pb(lpf[i]);
    }
    primes.erase(unique(all(primes)), primes.end());

    int g = 2;
    for (; g < mod; g++) {
      if (gcd(g, mod) != 1) continue;
      bool ok = true;
      for (auto e : primes) {
        ok = ok and mod_pow(g, phi[mod] / e, mod) != 1;
      }
      if (ok) break;
    }
    if (g == mod) {
      cout << "No\n";
      continue;
    }

    vc ans(N, vi(N));
    vc<bool> seen(mod, false);
    int b = 1;
    rep(i, 0, 2) {
      rep(j, 0, 2) {
        if (seen[b]) {
          for (b = 1; seen[b]; b++);
        }
        rep(k, 0, (N + 1 - i) / 2) {
          rep(l, 0, (N + 1 - j) / 2) {
            ans[2 * k + i][2 * l + j] = b;
            seen[b] = true;
            (b *= g) %= mod;
          }
        }
        if (i == 1) {
          rep(k, 0, (N + 1 - i) / 2) {
            for (int l = 0, r = (N + 1 - j) / 2 - 1; l < r; l++, r--) {
              swap(ans[2 * k + i][2 * l + j], ans[2 * k + i][2 * r + j]);
            }
          }
        }
        if (j == 1) {
          rep(k, 0, (N + 1 - j) / 2) {
            for (int l = 0, r = (N + 1 - i) / 2 - 1; l < r; l++, r--) {
              swap(ans[2 * l + i][2 * k + j], ans[2 * r + i][2 * k + j]);
            }
          }
        }
      }
    }
    bool ok = true;
    rep(i, 1, mod) { ok = ok and seen[i]; }
    if (!ok) {
      cout << "No\n";
      continue;
    }

    int r = 1;
    rep(i, 0, 2) {
      rep(j, 0, 2) { (r *= ans[i][j]) %= mod; }
    }
    int d = 0;
    for (; d < phi[mod]; d++) {
      if (r * mod_pow(g, 4 * d, mod) % mod == R) break;
    }
    if (d == phi[mod]) {
      cout << "No\n";
      continue;
    }
    for (auto &r : ans) {
      for (auto &e : r) {
        (e *= mod_pow(g, d, mod)) %= mod;
      }
    }

    cout << "Yes\n";
    for (auto r : ans) {
      for (auto e : r) {
        cout << e << ' ';
      }
      cout << '\n';
    }

    // rep(i, 0, N - 1) {
    //   cerr << '\t';
    //   rep(j, 0, N - 1) {
    //     int prod = 1;
    //     rep(k, 0, 2) {
    //       rep(l, 0, 2) { (prod *= ans[i + k][j + l]) %= mod; }
    //     }
    //     cerr << prod << ' ';
    //   }
    //   cerr << '\n';
    // }
  }
}
