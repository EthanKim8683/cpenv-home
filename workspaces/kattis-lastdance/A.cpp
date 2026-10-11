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
    int N, Q, G;
    cin >> N >> Q >> G;

    map<int, int> counts;
    map<int, int> genres;
    while (Q--) {
      char t;
      cin >> t;

      if (t == 'P') {
        int s, a;
        cin >> s >> a;
        s--;

        rep(j, 0, a) {
          int i;
          cin >> i;
          i--;

          if (genres.contains(i)) {
            counts[genres[i]] -= 1;
          }
          genres[i] = s;
          counts[genres[i]] += 1;
        }
      } else {
        int s;
        cin >> s;
        s--;

        cout << counts[s] << '\n';
      }
    }
  }
}
