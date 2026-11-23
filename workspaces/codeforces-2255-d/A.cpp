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

const int LOGA = 30;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // read editorial
  //
  // i had the observations i just had a bad greedy proof

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    auto check = [&](int x) -> bool {
      priority_queue<int> pq(all(A));
      for (int i = x - 1; i >= 0 and !pq.empty(); i--) {
        int a = pq.top(), b = 1ll << min(i, LOGA);
        pq.pop();
        if (a > b) {
          pq.push(a - b);
        }
      }
      return pq.empty();
    };
    int l = N, r = N + LOGA + 1;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l << '\n';
  }
}
