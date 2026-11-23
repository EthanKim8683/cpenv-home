#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define ll long long
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

const int MAXA = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<tuple<ll, int, int>> pool;
    rep(i, 0, N) {
      rep(j, 1, min(K + 2, i + 1)) {
        int d = A[i] - A[i - j];
        if (d % j != 0) continue;
        d /= j;
        pool.eb(d, A[i] - (ll) i * d, i - j);
        pool.eb(d, A[i] - (ll) i * d, i);
      }
    }
    sort(all(pool));
    pool.erase(unique(all(pool)), pool.end());
    auto key = [&](tuple<ll, int, int> x) -> pair<ll, int> {
      return {get<0>(x), get<1>(x)};
    };
    auto value = [&](tuple<ll, int, int> x) -> int { return get<2>(x); };
    int ans = 0;
    for (int l = 0, r = l; l < sz(pool); l = r) {
      for (; r < sz(pool) and key(pool[l]) == key(pool[r]); r++);
      for (int l2 = l, r2 = l; l2 < r; l2++) {
        for (; r2 < r and
               (value(pool[r2]) - value(pool[l2]) + 1) - (r2 - l2 + 1) <= K;
             r2++) {
          chmax(ans, min(K + (r2 - l2 + 1), N));
        }
      }
    }
    cout << ans << '\n';
  }
}
