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
    int N, M;
    cin >> N >> M;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(M);
    for (auto &e : B) cin >> e;

    auto sum = [&](vi A) -> int {
      int rv = 0;
      rep(i, 0, sz(A) - 1) { rv += A[i] - A[i + 1] + 1; }
      rv += A.back();
      return rv;
    };

    cout << (sum(B) <= sum(A) ? 1 : 2) << '\n';
  }
}
