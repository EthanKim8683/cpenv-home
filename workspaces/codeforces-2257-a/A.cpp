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
    int N, M;
    cin >> N >> M;

    vc<string> W(N);
    for (auto &e : W) cin >> e;

    vc<string> A(M);
    for (auto &e : A) cin >> e;

    vc<bool> seen(26, false);
    for (auto e : W) {
      seen[e[0] - 'a'] = true;
    }

    bool ans = true;
    for (auto r : A) {
      for (auto e : r) {
        ans = ans and seen[e - 'A'];
      }
    }
    cout << (ans ? "YES" : "NO") << '\n';
  }
}
