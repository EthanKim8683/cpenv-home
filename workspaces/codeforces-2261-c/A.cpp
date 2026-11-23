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

    vi counts(2, 0);
    for (auto e : A) {
      counts[e % 2]++;
    }

    if (counts[1] % 2 == 0) {
      if (counts[1] == 0) {
        if (counts[0] == 0) {
          cout << "Larpity\n";
        } else {
          cout << "Moggity\n";
        }
      } else {
        cout << "Moggity\n";
      }
    } else {
      if (counts[1] == 1) {
        if (counts[0] == 0) {
          cout << "Moggity\n";
        } else {
          if (counts[0] > 1) {
            cout << "Moggity\n";
          } else {
            cout << "Larpity\n";
          }
        }
      } else {
        if (counts[1] == 3) {
          if (counts[0] == 0) {
            cout << "Larpity\n";
          } else {
            cout << "Moggity\n";
          }
        } else {
          cout << "Moggity\n";
        }
      }
    }
  }
}
