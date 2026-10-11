#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

#include <tr2/dynamic_bitset>

using namespace std;
using namespace tr2;

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

const int MAXN = 2000;
const int MAXA = 2000;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

using BS = bitset<2000000 + 1>;
BS subset_sum_speedup_1(const vi &w) {
  map<int, int> occ;
  for (auto e : w) occ[e]++;
  BS rv;
  rv[0] = 1;
  for (auto [x, n] : occ) {
    rv |= rv << x, n--;
    if (n % 2) rv |= rv << x, n--;
    if (n) occ[2 * x] += n / 2;
  }
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  auto dp = subset_sum_speedup_1(A);
  int i = (accumulate(all(A), 0ll) + 1) / 2;
  for (; i <= MAXN * MAXA; i++) {
    if (dp[i]) break;
  }
  cout << i << '\n';
}
