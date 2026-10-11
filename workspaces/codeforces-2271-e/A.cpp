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

const int LOGN = 18;

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

    vi A(N);
    for (auto &e : A) cin >> e;

    auto check = [&](int x) -> bool {
      priority_queue<int> pq;
      for (auto e : A) {
        pq.push(e);
      }

      int k = K + x + N + x - 1, d = 0;
      while (sz(pq) > 0) {
        int e = pq.top();
        pq.pop();
        if (e > k) {
          pq.push((e + 1) / 2);
          pq.push((e + 1) / 2);
          d += 1;
          if (d > x) return false;
        } else {
          k--;
        }
      }
      return true;
    };
    int l = 0, r = N * LOGN;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l + N + l << '\n';
  }
}
