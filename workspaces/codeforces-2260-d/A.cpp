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

    string S;
    cin >> S;

    S = '0' + S;

    bool ok = true;
    rep(i, 0, sz(S) - 1) { ok = ok and S.substr(i, 2) != "00"; }
    if (!ok) {
      cout << "-1\n";
      continue;
    }

    vc<pair<char, int>> groups;
    for (int i = 0, j; i < sz(S); i = j) {
      for (j = i; j < sz(S); j++) {
        if (S[j] != S[i]) break;
      }
      groups.eb(S[i], j - i);
    }

    ok = true;
    rep(i, 0, sz(S) - 1) {
      ok = ok and S.substr(i, 2) != "+-";
      ok = ok and S.substr(i, 2) != "-+";
    }
    rep(i, 0, sz(groups) - 1) {
      auto [c, n] = groups[i];
      if (c == '+' or c == '-') {
        ok = ok and n % 2 == 1;
      }
    }
    if (ok) {
      cout << "1\n";
      continue;
    }

    ok = true;
    rep(i, 0, sz(S) - 3) {
      ok = ok and S.substr(i, 4) != "-++-";
      ok = ok and S.substr(i, 4) != "+--+";
    }
    if (ok) {
      cout << "2\n";
      continue;
    }

    cout << "3\n";
  }
}
