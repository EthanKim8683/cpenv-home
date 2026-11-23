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

    sort(all(A));
    sort(all(B));
    int i = 0, a1 = 0, a2 = 0, b = 0;
    bool ok = true;
    for (auto e : B) {
      while (i < N and A[i] < e) {
        if (b > 0) {
          b--;
          a2++;
        } else {
          a1++;
        }
        i++;
      }
      ok = ok and a1 + a2 >= 1;
      if (a1 >= 1) {
        a1--;
        b++;
      } else {
        a2--;
        b += 2;
      }
    }
    ok = ok and N - i >= b;
    cout << (ok ? "YES" : "NO") << '\n';
  }
}
