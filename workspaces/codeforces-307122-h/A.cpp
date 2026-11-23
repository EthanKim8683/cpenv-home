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

  auto query = [&](int r1, int c1, int r2, int c2) -> bool {
    cout << "? " << r1 + 1 << ' ' << c1 + 1 << ' ' << r2 + 1 << ' ' << c2 + 1
         << endl;
    string yn;
    cin >> yn;
    if (yn == "BAD") {
      exit(0);
    }
    return yn == "YES";
  };

  auto answer = [&](string S) -> void { cout << "! " << S << endl; };

  string S1 = "";
  int r = 0, c = 0;
  rep(i, 0, N - 1) {
    if (r + 1 < N and query(r + 1, c, N - 1, N - 1)) {
      S1 += 'D';
      r++;
    } else {
      S1 += 'R';
      c++;
    }
  }
  string S2 = "";
  r = N - 1;
  c = N - 1;
  rep(i, 0, N - 1) {
    if (c - 1 >= 0 and query(0, 0, r, c - 1)) {
      S2 += 'R';
      c--;
    } else {
      S2 += 'D';
      r--;
    }
  }
  reverse(all(S2));
  answer(S1 + S2);
}
