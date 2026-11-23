#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/extc++.h>

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

    vi B(N);
    for (auto &e : B) cin >> e;

    vi inv_P(N);
    rep(i, 0, N) { inv_P[i] = B[i] + (N - 1 - i); }
    set<int> S(all(inv_P));
    if (!(sz(S) == N and *S.begin() == 0 and *prev(S.end()) == N - 1)) {
      cout << "-1\n";
      continue;
    }
    vi P(N);
    rep(i, 0, N) { P[inv_P[i]] = i; }
    for (auto e : P) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
