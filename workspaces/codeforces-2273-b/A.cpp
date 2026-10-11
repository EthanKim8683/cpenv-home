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

    vi ans;
    auto transform_back = [&](int i) -> int { return i + sz(ans); };

    auto op = [&](int i) -> void {
      int j = transform_back(i);
      if (0 <= j and j <= N - 1 + N - 1) {
        ans.pb(j);
      }
    };

    rep(i, 0, 3) {
      for (int j = 3 * N + i; j >= -3 * N + i; j -= 3) {
        op(j);
      }
    }
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << 2 + e << ' ';
    }
    cout << '\n';
  }
}
