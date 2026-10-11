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

    auto build = [&](int x) -> vi {
      vi counts(x + 1);
      int n = 0;
      for (int i = x; i >= 1; i--) {
        counts[i] = min(x, N - n) / i;
        n += counts[i] * i;
      }
      if (n < N) return {};
      return counts;
    };
    auto check = [&](int x) -> bool { return !build(x).empty(); };
    int l = 0, r = N;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    auto counts = build(l);
    cout << l << '\n';
    int t = 1;
    rep(i, 1, l + 1) {
      rep(j, 0, counts[i]) {
        rep(k, 0, i) { cout << t << ' '; }
        t++;
      }
    }
    cout << '\n';
  }
}
