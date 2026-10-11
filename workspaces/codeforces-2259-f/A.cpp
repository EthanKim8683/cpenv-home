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

    string S;
    cin >> S;

    vi counts(2, 0);
    int ans = 0;
    for (auto e : A) {
      rep(i, e + 1, 2) { ans += counts[i]; }
      counts[e] += 1;
    }

    map<int, pii> groups;
    for (int i = 0, j; i < N; i = j) {
      for (j = i; j < N; j++) {
        if (A[j] != A[i]) break;
      }
      groups[i] = {A[i], j - i};
    }
    if (groups.begin()->sd.fs != 0) {
      groups[-1] = {0, 0};
    }
    if (groups.rbegin()->sd.fs != 1) {
      groups[N] = {1, 0};
    }

    auto shrink = [&](auto it) -> void {
      it->sd.sd -= 1;
      if (it == groups.begin()) return;
      if (next(it) == groups.end()) return;
      if (it->sd.sd == 0) {
        prev(it)->sd.sd += next(it)->sd.sd;
        it = groups.erase(it);
        groups.erase(it);
      }
    };

    cout << ans << ' ';
    for (auto e : S) {
      if (e == '1') {
        ans -= counts[0] - groups.begin()->sd.sd;
        auto it = next(groups.begin());
        shrink(it);
        prev(groups.end())->sd.sd += 1;
      } else {
        ans -= counts[1] - prev(groups.end())->sd.sd;
        auto it = prev(prev(groups.end()));
        shrink(it);
        groups.begin()->sd.sd += 1;
      }
      cout << ans << ' ';
    }
    cout << '\n';
  }
}
