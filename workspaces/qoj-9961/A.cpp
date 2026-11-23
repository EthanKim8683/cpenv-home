#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

const int MAXH = 1e9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // relative minimums invariably only give
  //
  // ah i know sol

  int N;
  cin >> N;

  vi H(N);
  for (auto &e : H) cin >> e;

  auto check = [&](int x) -> bool {
    int start = x, end = x, restart = x;
    bool give = true;
    for (auto e : H) {
      if (give) {
        if (e - x - (end - start) - (x - restart) > 0) {
          // e - x - (end - start) - (x - restart) - (x - start2) <= 0
          // start2 <= -e + x + (end - start) + (x - restart) + x
          start = -e + x + (end - start) + (x - restart) + x;
          end = x;
          give = false;
        } else {
          // if start2 <= start:
          //   e - start2 <= 0
          //   start2 >= e
          // elif start2 <= end:
          //   e - start2 - (start2 - start) <= 0
          //   2 * start2 >= e + start
          //   start2 >= ceil((e + start) / 2)
          // elif start2 <= restart:
          //   e - start2 - (end - start) <= 0
          //   start2 >= e - (end - start)
          // else:
          //   e - start2 - (end - start) - (start2 - restart) <= 0
          //   2 * start2 >= e - (end - start) + restart
          //   start2 >= ceil((e - (end - start) + restart) / 2)
          int start2a = e, start2b = (e + start + 1) / 2,
              start2c = e - (end - start),
              start2d = (e - (end - start) + restart + 1) / 2;

          set<int> start2s;
          if (start2a <= start) {
            start2s.insert(start2a);
          }
          if (start < start2b and start2b <= end) {
            start2s.insert(start2b);
          }
          if (end < start2c and start2c <= restart) {
            start2s.insert(start2c);
          }
          if (restart < start2d) {
            start2s.insert(start2d);
          }
          assert(sz(start2s) == 1);

          start = *start2s.begin();
          end = x;
          restart = x;
          give = true;
        }
      } else {
        if (e - start > 0) {
          // e - start - (start - start2) <= 0
          // start2 <= 2 * start - e
          end = start;
          start = 2 * start - e;
          give = false;
        } else {
          restart = end;
          end = start;
          start = e;
          give = true;
        }
      }
      if (start < 0) {
        return false;
      }
    }
    return give;
  };
  int l = 0, r = MAXH;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  cout << l << '\n';
}
