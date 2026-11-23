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
    int N, M, X, Y;
    cin >> N >> M >> X >> Y;

    vi A(X);
    for (auto &e : A) cin >> e;

    vi B(Y);
    for (auto &e : B) cin >> e;

    auto solve = [&](int N, int M, vi A, vi B, int base) -> int {
      vi C, A2, B2;
      for (auto e : A) {
        if (binary_search(all(B), e)) {
          C.pb(e);
        } else {
          A2.pb(e);
        }
      }
      for (auto e : B) {
        if (!binary_search(all(A), e)) {
          B2.pb(e);
        }
      }

      int sum = base, rv = 0;
      set<int> A3, B3;
      for (auto e : A2) {
        sum += e;
        A3.insert(e);
      }
      for (auto e : C) {
        sum += e;
        A3.insert(e);
      }
      for (auto e : B2) {
        sum += e;
        B3.insert(e);
      }
      set<int, greater<>> A4;
      while (sz(A3) > N) {
        int e = *A3.begin();
        sum -= e;
        A4.insert(e);
        A3.erase(e);
      }
      while (sz(B3) > M) {
        int e = *B3.begin();
        sum -= e;
        B3.erase(e);
      }
      chmax(rv, sum);
      reverse(all(C));
      for (auto e : C) {
        if (A3.contains(e)) {
          A3.erase(e);
          B3.insert(e);
        } else {
          sum += e;
          A4.erase(e);
          B3.insert(e);
        }
        while (sz(A3) < N and sz(A4) > 0) {
          int e = *A4.begin();
          sum += e;
          A3.insert(e);
          A4.erase(e);
        }
        while (sz(B3) > M) {
          int e = *B3.begin();
          sum -= e;
          B3.erase(e);
        }
        chmax(rv, sum);
      }
      return rv;
    };
    vi C, A2, B2;
    for (auto e : A) {
      if (binary_search(all(B), e)) {
        C.pb(e);
      } else {
        A2.pb(e);
      }
    }
    for (auto e : B) {
      if (!binary_search(all(A), e)) {
        B2.pb(e);
      }
    }
    int ans = 0;
    if (sz(C) > 0) {
      vi A3 = A, B3 = B;
      A3.erase(find(all(A3), C.back()));
      B3.erase(find(all(B3), C.back()));
      chmax(ans, solve(N - 1, M - 1, A3, B3, C.back()));
    }
    if (sz(A2) > 0) {
      vi A3 = A, B3 = B;
      A3.erase(find(all(A3), A2.back()));
      chmax(ans, solve(N - 1, M - 1, A3, B3, A2.back()));
    }
    if (sz(B2) > 0) {
      vi A3 = A, B3 = B;
      B3.erase(find(all(B3), B2.back()));
      chmax(ans, solve(N - 1, M - 1, A3, B3, B2.back()));
    }
    cout << ans << '\n';
  }
}
