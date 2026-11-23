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

const int LOGK = 30;

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

    vi basis(LOGK, -1), masks(LOGK, -1), sums(LOGK, -1);
    auto insert = [&](int x) -> void {
      int mask = 0, sum = x;
      for (int i = LOGK - 1; i >= 0; i--) {
        if (sum >> i & 1) {
          if (sums[i] == -1) {
            mask ^= 1ll << i;
            basis[i] = x;
            masks[i] = mask;
            sums[i] = sum;
          } else {
            mask ^= masks[i];
            sum ^= sums[i];
          }
        }
      }
    };
    auto query = [&](int x) -> int {
      int mask = 0, sum = x;
      for (int i = LOGK - 1; i >= 0; i--) {
        if (sum >> i & 1) {
          if (sums[i] == -1) return -1;
          mask ^= masks[i];
          sum ^= sums[i];
        }
      }
      return mask;
    };

    rep(i, 1, N) { insert(i); }
    int mask = query(N ^ K);
    if (mask == -1) {
      cout << "NO\n";
      continue;
    }
    vi special;
    special.pb(0);
    rep(i, 0, LOGK) {
      if (~mask >> i & 1) continue;
      special.pb(basis[i]);
    }
    sort(all(special));

    vc<bool> is_special(N, false);
    for (auto e : special) {
      is_special[e] = true;
    }

    cout << "YES\n";
    rep(i, 0, N) {
      if (is_special[i]) continue;
      cout << i << ' ';
    }
    for (auto e : special) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
