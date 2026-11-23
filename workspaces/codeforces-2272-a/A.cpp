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
    int N, K;
    cin >> N >> K;
    K--;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto solve = [&](vi A) -> int {
      vi mexes;
      int mex = 0;
      vc<bool> seen(N, false);
      for (auto e : A) {
        seen[e] = true;
        while (mex < N and seen[mex]) {
          mex++;
        }
        mexes.pb(mex);
      }
      sort(all(mexes));
      reverse(all(mexes));
      return mexes[K];
    };

    tuple<int, int, int> ans = {solve(A), N, N};
    rep(i, 0, N) {
      rep(j, i + 1, N) {
        swap(A[i], A[j]);
        chmax(ans, tuple{solve(A), i, j});
        swap(A[i], A[j]);
      }
    }
    auto [v, l, r] = ans;
    if (l == N) {
      cout << "-1\n";
      continue;
    }
    cout << l + 1 << ' ' << r + 1 << '\n';
  }
}
