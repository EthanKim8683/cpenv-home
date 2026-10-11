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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;
  A.insert(A.begin(), 0);

  vi B(N);
  for (auto &e : B) cin >> e;
  B.insert(B.begin(), 0);

  int bmin = INF, abest = -INF;
  for (int i = N; i >= 0; i--) {
    if (A[i] <= bmin) {
      chmax(abest, A[i]);
    }
    chmin(bmin, B[i]);
  }

  int amax = -INF, bbest = INF;
  for (int i = N; i >= 0; i--) {
    if (B[i] >= amax) {
      chmin(bbest, B[i]);
    }
    chmax(amax, A[i]);
  }

  int ans = abest;
  if (*max_element(all(A)) > bbest) {
    chmax(ans, bbest);
  }
  cout << ans << '\n';
}
