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

    if (N == 1) {
      cout << "FastestFinger\n";
    } else if (N % 2 == 1) {
      cout << "Ashishgup\n";
    } else {
      if (__builtin_popcount(N) == 1) {
        if (N == 2) {
          cout << "Ashishgup\n";
        } else {
          cout << "FastestFinger\n";
        }
      } else {
        if (N % 4 == 0) {
          cout << "Ashishgup\n";
        } else {
          bool is_prime = true;
          for (int i = 2; i * i <= N / 2; i++) {
            is_prime = is_prime and N / 2 % i != 0;
          }
          if (is_prime) {
            cout << "FastestFinger\n";
          } else {
            cout << "Ashishgup\n";
          }
        }
      }
    }
  }
}
