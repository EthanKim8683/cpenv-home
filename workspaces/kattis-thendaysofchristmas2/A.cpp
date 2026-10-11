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
const int MAXN = 1e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  vi fact(MAXN + 1);
  fact[0] = 1;
  rep(i, 1, MAXN + 1) { fact[i] = fact[i - 1] * i % MOD; }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<pii> blocks(N);
    for (auto &[l, w] : blocks) {
      cin >> l >> w;
      if (l < w) {
        swap(l, w);
      }
    }

    sort(all(blocks), [&](pii a, pii b) -> bool { return a > b; });

    bool ok = true;
    rep(i, 0, N - 1) {
      auto [l1, w1] = blocks[i];
      auto [l2, w2] = blocks[i + 1];
      ok = ok and l1 >= l2 and w1 >= w2;
    }
    if (!ok) {
      cout << "0\n";
      continue;
    }

    int ans = 1;
    auto [l, w] = blocks[0];
    if (l != w) {
      (ans *= 2) %= MOD;
    }
    rep(i, 1, N) {
      auto [l1, w1] = blocks[i - 1];
      auto [l2, w2] = blocks[i];
      int contrib = 0;
      (contrib += (l1 - l2 + 1) * (w1 - w2 + 1)) %= MOD;
      if (l2 != w2) {
        (contrib += max(l1 - w2 + 1, 0ll) * max(w1 - l2 + 1, 0ll)) %= MOD;
      }
      (ans *= contrib) %= MOD;
    }

    map<pii, int> counts;
    for (auto e : blocks) {
      counts[e] += 1;
    }
    for (auto [block, count] : counts) {
      (ans *= fact[count]) %= MOD;
    }

    cout << ans << '\n';
  }
}
