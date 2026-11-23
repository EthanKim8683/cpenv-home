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
const int INF = 1e18;

struct fenwick_tree {
  int n;
  vi d;
  fenwick_tree(int _n) : n(_n + 1), d(n, 0) {}
  void add(int i, int x) {
    for (i++; i < n; i += i & -i) d[i] += x;
  }
  int sum(int i) {
    int rv = 0;
    for (; i; i -= i & -i) rv += d[i];
    return rv;
  }
  // int lower_bound(int x) {
  //   if (x <= 0) return -1;
  //   int i = 0;
  //   for (int j = 1 << __lg(n); j; j >>= 1) {
  //     if (i + j < n and d[i + j] < x) i += j, x -= d[i];
  //   }
  //   return i;
  // }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vi A(N);
    for (auto &e : A) cin >> e;

    vi P(N);
    for (auto &e : P) {
      cin >> e;
      e--;
    }

    vi index(N);
    rep(i, 0, N) { index[P[i]] = i; }

    vc<bool> cut(N, false);
    vi size(N);
    auto dfs1 = [&](auto self, int a, int p) -> int {
      size[a] = 1;
      for (auto b : adj[a]) {
        if (b == p or cut[b]) continue;
        size[a] += self(self, b, a);
      }
      return size[a];
    };

    auto dfs2 = [&](auto self, int a, int p, int n) -> int {
      for (auto b : adj[a]) {
        if (b == p or cut[b]) continue;
        if (size[b] * 2 > n) return self(self, b, a, n);
      }
      return a;
    };

    int Asum = 0;
    for (auto e : A) {
      (Asum += e) %= MOD;
    }
    vi par(N), sums(N);
    auto dfs6 = [&](auto self, int a, int p) -> void {
      par[a] = p;
      sums[a] = A[a];
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        (sums[a] += sums[b]) %= MOD;
      }
    };
    dfs6(dfs6, 0, -1);

    auto subtree_sum = [&](int a0, int p0) -> int {
      // auto dfs6 = [&](auto self, int a, int p) -> int {
      //   int rv = A[a];
      //   for (auto b : adj[a]) {
      //     if (b == p) continue;
      //     rv += self(self, b, a);
      //   }
      //   return rv;
      // };
      // return dfs6(dfs6, a0, p0);
      if (p0 == par[a0]) return sums[a0];
      return (Asum - sums[p0]) % MOD;
    };

    vc<tuple<int, int, int>> seen;
    auto dfs4 = [&](auto self, int a, int p, int x) -> void {
      chmin(x, index[a]);
      seen.eb(a, x, subtree_sum(a, p));
      for (auto b : adj[a]) {
        if (b == p or cut[b]) continue;
        self(self, b, a, x);
      }
    };

    vi ans(N, 0);
    fenwick_tree ft(N);
    auto dfs3 = [&](auto self, int a) -> void {
      a = dfs2(dfs2, a, -1, dfs1(dfs1, a, -1));
      cut[a] = true;

      vc<pair<int, vc<tuple<int, int, int>>>> seens;
      for (auto b : adj[a]) {
        if (cut[b]) continue;
        seen.clear();
        dfs4(dfs4, b, a, index[a]);
        seens.eb(b, seen);
      }

      for (auto [b, seen] : seens) {
        for (auto [a, x, sum] : seen) {
          if (index[a] == x) {
            ft.add(x, sum);
          }
        }
      }

      (ans[a] += ft.sum(index[a] + 1) + Asum) %= MOD;

      for (auto [b, seen] : seens) {
        for (auto [a, x, sum] : seen) {
          if (index[a] == x) {
            ft.add(x, -sum);
          }
        }

        ft.add(index[a], subtree_sum(a, b));

        for (auto [a, x, sum] : seen) {
          (ans[a] += ft.sum(x + 1)) %= MOD;
        }

        ft.add(index[a], -subtree_sum(a, b));

        for (auto [a, x, sum] : seen) {
          if (index[a] == x) {
            ft.add(x, sum);
          }
        }
      }

      for (auto [b, seen] : seens) {
        for (auto [a, x, sum] : seen) {
          if (index[a] == x) {
            ft.add(x, -sum);
          }
        }
      }

      for (auto b : adj[a]) {
        if (cut[b]) continue;
        self(self, b);
      }
    };
    dfs3(dfs3, 0);

    for (auto e : ans) {
      cout << (e + MOD) % MOD << ' ';
    }
    cout << '\n';
  }
}
