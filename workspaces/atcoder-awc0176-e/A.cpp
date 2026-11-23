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

  vi A(N);
  for (auto &e : A) cin >> e;

  vi B(N);
  for (auto &e : B) cin >> e;

  auto solve = [&](vi A, vi B) -> int {
    sort(all(A));
    sort(all(B));
    int rv = 0;
    for (int i = sz(A) - 1, j = sz(B) - 1; i >= 0 and j >= 0;) {
      if (A[i] > B[j]) {
        rv++;
        i--;
        j--;
      } else {
        j--;
      }
    }
    return rv;
  };

  sort(all(A));
  int l = 0;
  while (l < N and A[l] <= B.back()) {
    l++;
  }

  int d = 1;
  if (l == N) {
    l = 0;
    d = 0;
  }

  auto check = [&](int x) -> bool {
    vi A2 = A, B2 = B;
    A2.erase(A2.begin() + x);
    B2.pop_back();
    return solve(A2, B2) + d == solve(A, B);
  };
  int r = N - 1;
  while (l < r) {
    int m = l + (r - l + 1) / 2;
    check(m) ? l = m : r = m - 1;
  }
  cout << solve(A, B) << ' ' << A[l] - B.back() << '\n';
}
