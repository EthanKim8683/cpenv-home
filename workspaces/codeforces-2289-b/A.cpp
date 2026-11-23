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

  // at pos i, there are i before and K-1-i after, so all in range [i,
  // N-(K-1-i)=i+N-K+1) must be same
  //
  // try sliding windows of size N-K+1

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    multiset<int> S;
    rep(i, 0, N - K + 1) { S.insert(A[i]); }
    int ans = 0;
    rep(i, 0, N - (N - K + 1) + 1) {
      if (*S.begin() == *S.rbegin()) {
        ans += 1;
      }
      if (i + (N - K + 1) < N) {
        S.erase(S.find(A[i]));
        S.insert(A[i + (N - K + 1)]);
      }
    }
    cout << ans << '\n';
  }
}
