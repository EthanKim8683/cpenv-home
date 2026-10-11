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

  // fix k
  //
  // only look at A[i] >= k
  //
  // sort
  //
  // sum <= T
  //
  // if we can't achieve k, k must be smaller
  //
  // else k is ok

  int N, T;
  cin >> N >> T;

  vc<pii> problems(N);
  for (auto &[a, t] : problems) {
    cin >> a >> t;
  }

  auto solve = [&](int k) -> vi {
    vi order;
    rep(i, 0, N) {
      auto [a, t] = problems[i];
      if (a < k) continue;
      order.pb(i);
    }
    sort(all(order),
         [&](int a, int b) -> bool { return problems[a].sd < problems[b].sd; });
    vi p;
    int sum = 0;
    for (auto e : order) {
      auto [a, t] = problems[e];
      if (sum + t > T) break;
      p.pb(e);
      sum += t;
    }
    return p;
  };

  auto check = [&](int k) -> bool { return sz(solve(k)) >= k; };

  int l = 0, r = N;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << l << '\n';
  auto ans = solve(l);
  ans.resize(l);
  cout << sz(ans) << '\n';
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}
