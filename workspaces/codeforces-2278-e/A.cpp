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

    if (N == 1) {
      cout << A[0] << '\n';
      continue;
    }

    vc<priority_queue<int>> pq(2);
    int sum = 0;
    rep(i, 0, N) {
      sum += A[i];
      pq[i % 2].push(-A[i]);
    }
    while (true) {
      int a = pq[0].top(), b = pq[1].top();
      pq[0].pop();
      pq[1].pop();
      if (a + b <= 0) break;
      sum += 2 * (a + b);
      pq[1].push(-a);
      pq[0].push(-b);
    }
    cout << sum << '\n';
  }
}
