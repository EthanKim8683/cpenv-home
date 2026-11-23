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
    int N, X;
    cin >> N >> X;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto check = [&](int x) -> bool {
      vi cells = A;
      vc<bool> used(N, false);
      int count = 0;
      for (int i = 0, j = 0; i < N;) {
        for (; j < N and cells[j] <= cells[i] + x; j++);
        if (j - 1 != i) {
          used[j - 1] = true;
          i++;
        } else if (used[i]) {
          i++;
        } else {
          count++;
          if (count > X) return false;
          cells[i] += x;
          used[i] = true;
        }
      }
      return true;
    };
    int l = 1, r = MAXA;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l << '\n';
  }
}
