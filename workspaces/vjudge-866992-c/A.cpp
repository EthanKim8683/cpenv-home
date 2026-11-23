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

  // for each player, we play with the other players and try to leave a player
  // that the chosen player can beat in the last battle. if the last battle is
  // 0, go for a greater player. if it's 1, go for a lesser player
  //
  // go in reverse? if it's 0, we have to have gotten rid of one greater. if
  // it's 1 we have to have gotten rid of one lesser. ah, but greater/lesser
  // than what? if we've gotten rid of one greater, we can use that to get rid
  // of other greaters or lessers! if we've gotten rid of one lesser, we can do
  // the same
  //
  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    string S;
    cin >> S;
  }
}
