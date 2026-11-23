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

  int N, K;
  cin >> N >> K;

  vc cubes(N, vi(6));
  for (auto &r : cubes) {
    for (auto &e : r) {
      cin >> e;
    }
  }

  // vi counts(10, 0);
  // for (auto r : cubes) {
  //   sort(all(r));
  //   r.erase(unique(all(r)), r.end());
  //   for (auto e : r) {
  //     counts[e]++;
  //   }
  // }

  // vi masks(10, (1 << 10) - 1);
  // for (auto r : cubes) {
  //   int mask = 0;
  //   for (auto e : r) {
  //     mask |= 1ll << e;
  //   }
  //   rep(i, 0, 10) {
  //     if (mask >> i & 1) continue;
  //     masks[i] &= ~mask;
  //   }
  // }

  vi counts(1 << 10, 0);
  for (auto r : cubes) {
    int mask = 0;
    for (auto e : r) {
      mask |= 1ll << e;
    }
    rep(i, 0, 1 << 10) {
      if ((i & mask) != 0) {
        counts[i]++;
      }
    }
  }

  auto inc = [&](vi x) -> vi {
    reverse(all(x));

    bool carry = true;
    for (int i = 0; i < sz(x) and carry; i++) {
      if (x[i] < 9) {
        x[i]++;
        carry = false;
      } else {
        x[i] = 0;
      }
    }
    if (carry) {
      x.pb(1);
    }

    reverse(all(x));
    return x;
  };

  auto fix = [&](vi x, int mask, int need) -> vi {
    reverse(all(x));

    int ub = 0;
    rep(i, 0, 10) {
      if (~mask >> i & 1) continue;
      ub = i;
    }

    if (sz(x) < need) {
      x.resize(need, 0);
    }
    x.pb(0);

    int nz = 0, have = 0;
    for (int i = sz(x) - 1; i >= 0; i--) {
      while (true) {
        if (x[i] != 0) {
          nz++;
        }
        if (nz > 0 and (mask >> x[i] & 1)) {
          have++;
        }

        int possible = 0;
        if (ub == 9) {
          possible += i;
        } else {
          for (int j = i - 1; j >= 0; j--) {
            if (j >= need - have) {
              if (x[j] < 9) {
                possible += j;
                break;
              }
            } else {
              if (x[j] > ub) break;
              if (x[j] < ub) {
                possible += j + 1;
                break;
              }
              possible++;
            }
          }
        }
        if (possible >= need - have) break;

        if (nz > 0 and (mask >> x[i] & 1)) {
          have--;
        }
        if (x[i] != 0) {
          nz--;
        }

        x[i]++;
        rep(j, 0, i) { x[j] = 0; }
      }
    }

    while (x.back() == 0) {
      x.pop_back();
    }

    reverse(all(x));
    return x;
  };

  using T = pair<vi, int>;
  auto less = [&](T &a, T &b) -> bool {
    auto &[x1, i1] = a;
    auto &[x2, i2] = b;
    if (sz(x1) > sz(x2)) return true;
    if (sz(x1) < sz(x2)) return false;
    return x1 > x2;
  };
  priority_queue<T, vc<T>, decltype(less)> pq(less);
  // rep(i, 0, 10) { pq.emplace(fix({1}, masks[i], counts[i] + 1), i); }
  rep(i, 1, 1 << 10) { pq.emplace(fix({1}, i, counts[i] + 1), i); }

  int count = 0;
  vi xprev;
  while (sz(pq) > 0 and count < K) {
    auto [x, i] = pq.top();
    pq.pop();

    if (x != xprev) {
      for (auto e : x) {
        cout << e;
      }
      cout << ' ';
      count++;
      xprev = x;
    }

    // pq.emplace(fix(inc(x), masks[i], counts[i] + 1), i);
    pq.emplace(fix(inc(x), i, counts[i] + 1), i);
  }
  cout << '\n';
}
