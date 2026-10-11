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

    string S;
    cin >> S;

    vi counts(2, 0);
    rep(i, 0, 2 * N) {
      if (S[i] != '1') continue;
      if (S[(i + 1) % (2 * N)] == '1') {
        counts[(i + 1) % 2] += 1;
      } else {
        counts[i % 2] += 1;
      }
    }
    for (auto e : counts) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
