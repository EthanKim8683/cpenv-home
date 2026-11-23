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

const int MOD = 998244353;
const int MAXX = 2e5;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int x, int y) {
  int rv = 1;
  for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
    if (y & 1) (rv *= x) %= MOD;
  return rv;
}

int mod_inv(int x) { return mod_pow(x, MOD - 2); }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // merge sort tree
  //
  // keep track of indices of repeats
  //
  // if there are any deletes, we do at most N repeats
  //
  // if there are no subtractions yet, then just use count and pow2 to solve
  // easily.
  //
  // once we encounter a subtraction, there's a cost to repeating
  //
  // only pay attention to the last 2e5 subtracts/last 2e5 repeats basically

  int N;
  cin >> N;

  vc<pii> ops(N);
  for (auto &[t, x] : ops) {
    cin >> t;
    if (t != 3) {
      cin >> x;
    }
  }

  vc<vc<pii>> st(2 * (N + 1));
  bool found = false;
  vi counts(MAXX + 1, 0);
  vc<tuple<int, int, int>> ops2;
  ops2.eb(-1, 0, -1);
  int pow2 = 1;
  rep(i, 0, N) {
    auto [t, x] = ops[i];
    if (found) {
      if (t == 1) {
        st[N + 1 + i + 1].eb(x, 1);
      } else if (t == 2) {
        ops2.eb(2, i + 1, x);
      } else {
        ops2.eb(3, i + 1, -1);
      }
    } else {
      if (t == 1) {
        (counts[x] += mod_inv(pow2)) %= MOD;
      } else if (t == 2) {
        rep(j, 0, MAXX + 1) {
          if (counts[j] == 0) continue;
          st[N + 1 + i].eb(j, counts[j] * pow2 % MOD);
        }
        ops2.eb(2, i + 1, x);
        found = true;
      } else {
        (pow2 *= 2) %= MOD;
      }
    }
  }
  ops2.eb(-1, N + 1, -1);
  rep(i, N + 1, 2 * (N + 1)) { sort(all(st[i])); }
  for (int i = N; i >= 1; i--) {
    merge(all(st[i << 1]), all(st[i << 1 | 1]), back_inserter(st[i]));
  }
  rep(i, 1, 2 * (N + 1)) {
    st[i].eb(MAXX + 1, 0);
    for (int j = sz(st[i]) - 2; j >= 0; j--) {
      (st[i][j].sd += st[i][j + 1].sd) %= MOD;
    }
  }
  auto query = [&](int l, int r, int x) -> int {
    int rv = 0;
    auto add = [&](int i) -> void {
      (rv += lower_bound(all(st[i]), pii{x + 1, 0})->sd) %= MOD;
    };
    for (l += N + 1, r += N + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) add(l++);
      if (r & 1) add(--r);
    }
    return rv;
  };

  if (!found) {
    int ans = 0;
    for (auto e : counts) {
      (ans += e * pow2) %= MOD;
    }
    cout << ans << '\n';
    exit(0);
  }

  int sum = 0, ans = 0;
  auto dfs = [&](auto self, int i) -> void {
    if (sum >= MAXX) return;
    auto [t, j, x] = ops2[i];
    (ans += query(get<1>(ops2[i]), get<1>(ops2[i + 1]), sum)) %= MOD;
    if (t == 2) {
      sum += x;
      self(self, i - 1);
    } else if (t == 3) {
      self(self, i - 1);
      self(self, i - 1);
    }
  };
  dfs(dfs, sz(ops2) - 2);
  cout << ans << '\n';
}
