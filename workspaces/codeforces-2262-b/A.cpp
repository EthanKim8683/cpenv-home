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

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int i, int dif) {  // a[i] += dif
    for (; i < sz(s); i |= i + 1) s[i] += dif;
  }
  int query(int i) {  // sum of values in [0, i)
    int r = 0;
    for (; i > 0; i &= i - 1) r += s[i - 1];
    return r;
  }
  int lower_bound(int sum) {  // min i st sum of [0, i] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    // (assumes a[i] >= 0)
    if (sum <= 0) return -1;
    int i = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (i + pw <= sz(s) && s[i + pw - 1] < sum) i += pw, sum -= s[i - 1];
    }
    return i;
  }
};

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

    vi A(N);
    for (auto &e : A) cin >> e;

    vi P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vi ans(N);
    FT ft(N);
    set<int> forfeits;
    for (int i = N - 1; i >= 0; i--) {
      int j = P[i];
      ft.update(j, A[j]);
      while (true) {
        int k = 0;
        auto it = forfeits.lower_bound(j);
        if (it != forfeits.begin()) {
          k = *prev(it);
        }

        if (ft.query(j) - ft.query(k) < A[j]) {
          if (forfeits.contains(j)) break;
          forfeits.insert(j);
        } else {
          if (forfeits.contains(j)) {
            forfeits.erase(j);
          }
        }

        it = forfeits.upper_bound(j);
        if (it == forfeits.end()) break;
        j = *it;
      }
      ans[i] = sz(forfeits) - 1;
    }
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
