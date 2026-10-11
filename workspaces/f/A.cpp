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

  int N;
  cin >> N;

  vc<pii> people(N);
  for (auto &[a, b] : people) {
    cin >> a >> b;
  }

  int sum = 0;
  for (auto [a, b] : people) {
    sum += b - a;
  }
  rep(i, 0, N) {
    auto [a, b] = people[i];
    if (sum + a <= b) {
      cout << i + 1 << '\n';
      exit(0);
    }
  }
  cout << "impossible\n";
}
