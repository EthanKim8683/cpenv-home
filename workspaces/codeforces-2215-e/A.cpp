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

    vc<pii> stars(N);
    for (auto &[x, y] : stars) {
      cin >> x >> y;
    }

    vi order(N);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return stars[a] < stars[b]; });

    vc<tuple<int, int, int>> ans;
    map<int, int> stack;
    int peak;
    bool first = true;
    for (auto e : order) {
      auto [x, y] = stars[e];
      if (first) {
        first = false;
      } else {
        if (y > peak) {
          auto it = stack.find(peak);
          int a = it->sd;
          while (next(it) != stack.end()) {
            int b = next(it)->sd;
            ans.eb(a, b, e);
            if (next(it)->fs > y) break;
            stack.erase(next(it));
            a = b;
          }
        } else {
          auto it = stack.find(peak);
          int a = it->sd;
          while (it != stack.begin()) {
            int b = prev(it)->sd;
            ans.eb(a, b, e);
            if (prev(it)->fs < y) break;
            stack.erase(prev(it));
            a = b;
          }
        }
      }
      stack.emplace(y, e);
      peak = y;
    }
    cout << sz(ans) << '\n';
    for (auto [a, b, c] : ans) {
      cout << a + 1 << ' ' << b + 1 << ' ' << c + 1 << '\n';
    }
  }
}
