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

    vc<pii> groups;
    for (int i = 0, j = 0; i < N; i = j) {
      for (; j < N and A[j] == A[i]; j++);
      groups.eb(A[i], j - i);
    }

    bool found = false;
    rep(i, 0, sz(groups) - 1) {
      if (groups[i].sd >= 2 and groups[i + 1].sd >= 2) {
        found = true;
      }
    }
    if (found) {
      cout << sz(groups) + 2 << '\n';
      continue;
    }

    found = false;
    rep(i, 0, sz(groups)) {
      if (groups[i].sd == 1) continue;
      if (i - 1 >= 0) {
        if (i - 2 >= 0) {
          found = found or groups[i - 2].fs != groups[i].fs;
        } else {
          found = true;
        }
      }
      if (i + 1 < sz(groups)) {
        if (i + 2 < sz(groups)) {
          found = found or groups[i + 2].fs != groups[i].fs;
        } else {
          found = true;
        }
      }
    }
    cout << (found ? sz(groups) + 1 : sz(groups)) << '\n';
  }
}
