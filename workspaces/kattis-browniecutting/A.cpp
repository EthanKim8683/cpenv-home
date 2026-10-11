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

  int N, K;
  cin >> N >> K;

  vc<pii> brownies(N);
  for (auto &[x, y] : brownies) {
    cin >> x >> y;
  }

  if (K == 0) {
    cout << "0\n";
    exit(0);
  }

  auto dist2 = [&](pii a, pii b) -> int {
    auto [x1, y1] = a;
    auto [x2, y2] = b;
    int dx = x2 - x1, dy = y2 - y1;
    return dx * dx + dy * dy;
  };

  int j = 0, d2 = 0;
  set<pii> pairs;
  auto bad = [&](int i, int j) -> bool {
    return ((i - j) % N + N) % N == 1 or ((j - i) % N + N) % N == 1;
  };
  auto see = [&](int i, int j) -> void {
    int d22 = dist2(brownies[i], brownies[j]);
    if (d22 > d2) {
      d2 = d22;
      pairs.clear();
    }
    if (d22 == d2 and !bad(i, j)) {
      int a = i, b = j;
      if (a > b) {
        swap(a, b);
      }
      pairs.emplace(a, b);
    }
  };
  rep(i, 0, N) {
    see(i, j);
    while (dist2(brownies[i], brownies[(j + 1) % N]) >=
           dist2(brownies[i], brownies[j])) {
      (j += 1) %= N;
      see(i, j);
    }
  }
  int count = sz(pairs);
  // int d2 = 0, count = 0;
  // rep(i, 0, N) {
  //   rep(j, i + 1, N) {
  //     int d22 = dist2(brownies[i], brownies[j]);
  //     if (d22 > d2) {
  //       d2 = d22;
  //       count = 0;
  //     }
  //     if (d22 == d2 and j - i != 1 and (i + N - j) % N != 1) {
  //       count += 1;
  //     }
  //   }
  // }
  auto check = [&](int x) -> bool {
    if (x <= count) {
      return 4 * x * x >= (K * K - 1) / d2 + 1;
    } else {
      return 4 * x * x > K * K / d2;
    }
  };
  int l, r;
  if (check(count)) {
    l = 0;
    r = count;
  } else {
    l = count + 1;
    r = 1e9;
  }
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  cout << l << '\n';
}
