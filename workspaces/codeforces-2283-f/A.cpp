#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/extc++.h>
#include <bits/stdc++.h>

using namespace std;
using namespace __gnu_pbds;

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

template <class T, class Compare = less<T>>
using ordered_set =
    tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

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

    vc<pii> ranges(N);
    rep(i, 1, N) {
      auto &[l, r] = ranges[i];
      cin >> l >> r;
      l--;
    }

    vc<vi> by_r(N + 1);
    rep(i, 1, N) { by_r[ranges[i].sd].pb(i); }

    ordered_set<int> heads;
    int ans = 0;
    rep(i, 0, N) {
      auto [l, r] = ranges[i];
      for (auto it = heads.lower_bound(l); it != heads.lower_bound(r);
           it = heads.erase(it));
      heads.insert(i);
      for (auto e : by_r[i + 1]) {
        auto [l, r] = ranges[e];
        ans += heads.order_of_key(r) - heads.order_of_key(l);
      }
    }
    cout << ans << '\n';
  }
}
