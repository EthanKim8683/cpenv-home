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

  int N, M, K;
  cin >> N >> M >> K;

  vi S(N);
  for (auto &e : S) cin >> e;

  vi R(M);
  for (auto &e : R) cin >> e;

  sort(all(S));
  sort(all(R));

  int ans = 0;
  for (int i = N - 1 - K, j = M - 1; i >= 0 and j >= 0;) {
    if (S[i] >= R[j]) {
      ans++;
      i--;
      j--;
    } else {
      j--;
    }
  }
  cout << ans << '\n';
}
