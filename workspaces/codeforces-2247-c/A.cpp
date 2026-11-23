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

    vi B(N);
    for (auto &e : B) cin >> e;

    if (A == B) {
      cout << "0\n";
      continue;
    }

    if (find(all(A), 1) == A.end()) {
      cout << "-1\n";
      continue;
    }

    if (find(all(B), 0) == B.end()) {
      cout << "-1\n";
      continue;
    }

    int sum = 0;
    rep(i, 0, N) {
      if (A[i] != B[i]) {
        sum += A[i];
      }
    }
    cout << (sum % 2 == 1 ? 1 : 2) << '\n';
  }
}
