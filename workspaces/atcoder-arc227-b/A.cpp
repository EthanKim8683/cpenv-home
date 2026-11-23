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

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  multiset<int> unused(all(A));
  vi B(N);
  rep(i, 0, N) {
    if (unused.contains(i)) {
      B[i] = i;
    } else {
      if (i == 0) break;
      auto it = unused.upper_bound(B[i - 1]);
      if (it == unused.begin()) break;
      B[i] = *prev(it);
    }
    unused.erase(unused.find(B[i]));
  }
  if (sz(unused) > 0) {
    cout << "No\n";
    exit(0);
  }
  cout << "Yes\n";
  for (auto e : B) {
    cout << e << ' ';
  }
  cout << '\n';
}
