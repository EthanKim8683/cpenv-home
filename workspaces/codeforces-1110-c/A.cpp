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

  vi memo = {0,   1,      1,      5,       1,      21,      1,      85, 73,
             341, 89,     1365,   1,       5461,   4681,    21845,  1,  87381,
             1,   349525, 299593, 1398101, 178481, 5592405, 1082401};

  int Q;
  cin >> Q;

  int i = 0;
  while (Q--) {
    int A;
    cin >> A;

    int B = (1ll << (__lg(A) + 1)) - 1;
    if (A == B) {
      cout << memo[__lg(A)] << '\n';
    } else {
      cout << B << '\n';
    }
  }
}
