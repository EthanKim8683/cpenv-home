#include <random>
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

string tf = "TF";

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  mt19937 rng(time(nullptr));

  int T;
  cin >> T;

  while (T--) {
    rep(i, 0, 100) {
      auto query = [&](char c) -> char {
        cout << c << endl;
        char rv;
        cin >> rv;
        return rv;
      };

      if (query(tf[rng() % 2]) == 'T') {
        query('F');
      } else {
        query('T');
      }
    }
  }
}
