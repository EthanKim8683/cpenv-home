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
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vi groups(N);
    rep(i, 0, N) { groups[A[i]] = i % 2; }

    vi counts(2, 0);
    counts[0] += 1;
    counts[(N - 1) % 2] += 1;
    bool ok = true;
    for (auto e : groups) {
      if (counts[e] == 0) {
        ok = false;
        break;
      }
      counts[e] -= 1;
      counts[e ^ 1] += 1;
    }
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
