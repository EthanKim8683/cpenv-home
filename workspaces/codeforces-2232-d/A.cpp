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

    vi A(N);
    for (auto &e : A) cin >> e;

    bool ok = true;
    rep(i, 0, N) { ok = ok and A[i] <= i; }
    if (!ok) {
      cout << "NO\n";
      continue;
    }

    vc<tuple<int, int, int>> ans;
    auto dfs = [&](auto self, int n, int a, int b, int c) -> void {
      if (n == 0) return;
      if (A[n - 1] == 0) {
        self(self, n - 1, a, c, b);
        ans.eb(n - 1, a, c);
        self(self, n - 1, b, a, c);
      } else {
        self(self, n - 1 - A[n - 1], a, c, b);
        ans.eb(n - 1, a, c);
        self(self, n - 1 - A[n - 1], b, c, a);
        self(self, n - 1, a, b, c);
      }
    };
    dfs(dfs, N, 0, 1, 2);
    cout << "YES\n";
    cout << sz(ans) << '\n';
    for (auto [id, from, to] : ans) {
      cout << id + 1 << ' ' << from + 1 << ' ' << to + 1 << '\n';
    }
  }
}
