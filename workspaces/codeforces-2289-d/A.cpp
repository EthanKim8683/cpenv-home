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

template <class S, class T = less<S>>
using ordered_set =
    tree<S, null_type, T, rb_tree_tag, tree_order_statistics_node_update>;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // sum is constant
  //
  // swap prefix sums i-1, i (can't swap with ps[0] tho)
  //
  // basically can we sort prefix sums??
  //
  // so if all prefix sums are non-negative this is possible and the answer is
  // the number of inversions

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ps(N);
    ps[0] = A[0];
    rep(i, 1, N) { ps[i] = ps[i - 1] + A[i]; }

    bool ok = true;
    for (auto e : ps) {
      ok = ok and e >= 0;
    }
    if (!ok) {
      cout << "-1\n";
      continue;
    }

    ordered_set<pii> os;
    int ans = 0;
    rep(i, 0, N) {
      ans += sz(os) - os.order_of_key({ps[i] + 1, -1});
      os.insert({ps[i], i});
    }
    cout << ans << '\n';
  }
}
