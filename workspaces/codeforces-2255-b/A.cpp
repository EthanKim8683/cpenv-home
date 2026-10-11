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

const int MOD = 998244353;
const int MAXN = 1e6;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
      if (y & 1) {
        (rv *= x) %= MOD;
      }
    }
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  vi inv_fact(MAXN + 1);
  rep(i, 0, MAXN + 1) { inv_fact[i] = mod_inv(fact[i]); }

  auto binom = [&](int n, int k) -> int {
    return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
  };

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;

    vi counts2(2, 0);
    rep(i, 0, N - 1) {
      if (S[i] != S[i + 1]) {
        counts2[S[i] - '0']++;
      }
    }
    counts2[S.back() - '0']++;

    if (counts2[0] == 0 or counts2[1] == 0) {
      cout << "1\n";
      continue;
    }

    vi counts(2, 0);
    for (auto e : S) {
      counts[e - '0'] += 1;
    }

    counts[0] -= counts2[0];
    counts[1] -= counts2[1];

    cout << binom(counts[0] + counts2[0] - 1, counts2[0] - 1) *
                binom(counts[1] + counts2[1] - 1, counts2[1] - 1) % MOD
         << '\n';
  }
}
