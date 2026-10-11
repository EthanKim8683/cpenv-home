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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vc<pii> ranges(N);
  for (auto &[l, r] : ranges) {
    cin >> l >> r;
  }

  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool {
    auto key = [&](int x) -> pii {
      auto [l, r] = ranges[x];
      return {-r, l};
    };
    return key(a) < key(b);
  });

  pii lmin = {INF, -1};
  for (auto e : order) {
    auto [l, r] = ranges[e];
    if (lmin.fs <= l) {
      cout << e + 1 << ' ' << lmin.sd + 1 << '\n';
      exit(0);
    }
    chmin(lmin, pii{l, e});
  }
  cout << "-1 -1\n";
}
