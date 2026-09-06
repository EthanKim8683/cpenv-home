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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

void sort_hld(std::vector<std::vector<int>> &adj, int r = 0) {
  auto dfs = [&](auto self, int a, int p) -> int {
    int rv = 1, nmax = 0;
    for (int i = 0; i < (int) adj[a].size(); i++) {
      if (adj[a][i] == p) {
        std::swap(adj[a][i], adj[a].back());
      }

      if (adj[a][i] == p) continue;
      int n = self(self, adj[a][i], a);
      rv += n;

      if (i == 0) {
        nmax = n;
      } else {
        if (n > nmax) {
          std::swap(adj[a][0], adj[a][i]);
          nmax = n;
        }
      }
    }
    return rv;
  };
  dfs(dfs, r, -1);
}

void sack(const std::function<void(int)> &insert,
          const std::function<void()> &clear,
          const std::function<void(int)> &callback,
          const std::vector<std::vector<int>> &adj, int r = 0) {
  int n = adj.size();

  std::vector<int> order(n);
  int t = 0;
  auto dfs = [&](auto self, int a, int p) -> void {
    order[t] = a;
    t++;

    int l = t;
    for (int i = 1; i < (int) adj[a].size(); i++) {
      if (adj[a][i] == p) continue;
      self(self, adj[a][i], a);
      clear();
    }
    int r = t;

    if ((int) adj[a].size() > 0 and adj[a][0] != p) {
      self(self, adj[a][0], a);
      for (int i = l; i < r; i++) {
        insert(order[i]);
      }
    }
    insert(a);

    callback(a);
  };
  dfs(dfs, r, -1);
}

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int i, int dif) {  // a[i] += dif
    for (; i < sz(s); i |= i + 1) s[i] += dif;
  }
  int query(int i) {  // sum of values in [0, i)
    int r = 0;
    for (; i > 0; i &= i - 1) r += s[i - 1];
    return r;
  }
  int lower_bound(int sum) {  // min i st sum of [0, i] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    // (assumes a[i] >= 0)
    if (sum <= 0) return -1;
    int i = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (i + pw <= sz(s) && s[i + pw - 1] < sum) i += pw, sum -= s[i - 1];
    }
    return i;
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi P(N);
    for (auto &e : P) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int x, y;
      cin >> x >> y;
      x--, y--;
      adj[x].pb(y);
      adj[y].pb(x);
    }

    FT ft(N + 2);
    rep(i, 0, N + 2) { ft.update(i, 1); }
    vi mex(N), mex2(N);
    auto dfs = [&](auto self, int a, int p) -> void {
      ft.update(P[a], -1);
      mex[a] = ft.lower_bound(1);
      ft.update(mex[a], -1);
      mex2[a] = ft.lower_bound(1);
      ft.update(mex[a], 1);
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
      ft.update(P[a], 1);
    };
    dfs(dfs, 0, -1);

    vi Pinv(N + 1, -1);
    rep(i, 0, N) { Pinv[P[i]] = i; }
    vi tin(N), tout(N);
    int t = 0;
    auto dfs2 = [&](auto self, int a, int p) -> void {
      tin[a] = t;
      t++;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
      tout[a] = t;
    };
    dfs2(dfs2, 0, -1);
    auto is_anc = [&](int a, int b) -> bool {
      return tin[a] <= tin[b] and tout[b] <= tout[a];
    };

    vc<vi> subtract(N);
    rep(i, 0, N) {
      int j = Pinv[mex[i]];
      if (j == -1) continue;
      if (!is_anc(i, j)) continue;
      subtract[j].pb(i);
    }

    vi cost(N, 0);
    FT ft2(N + 2), ft3(N + 2), ft4(N + 1), ft5(N + 1);
    vi updated, updated2;
    sort_hld(adj);
    sack(
        [&](int a) -> void {
          ft2.update(mex2[a], mex2[a]);
          ft3.update(mex2[a], 1);
          updated.pb(mex2[a]);
          ft4.update(mex[a], mex[a]);
          ft5.update(mex[a], 1);
          updated2.pb(mex[a]);
        },
        [&]() -> void {
          for (auto e : updated) {
            ft2.update(e, -e);
            ft3.update(e, -1);
          }
          updated.clear();
          for (auto e : updated2) {
            ft4.update(e, -e);
            ft5.update(e, -1);
          }
          updated2.clear();
        },
        [&](int a) -> void {
          for (auto b : subtract[a]) {
            cost[b] -=
                ft2.query(P[b]) + (ft3.query(N + 1) - ft3.query(P[b])) * P[b];
            cost[b] +=
                ft4.query(P[b]) + (ft5.query(N + 1) - ft5.query(P[b])) * P[b];
          }
          cost[a] +=
              ft2.query(P[a]) + (ft3.query(N + 1) - ft3.query(P[a])) * P[a];
        },
        adj);

    auto dfs3 = [&](auto self, int a, int p) -> array<int, 2> {
      array<int, 2> dp = {mex[a], 0};
      for (auto b : adj[a]) {
        if (b == p) continue;
        auto dp2 = self(self, b, a);
        dp = {dp[0] + dp2[0], max(dp[1] + dp2[0], dp[0] + dp2[1])};
      }
      chmax(dp[1], cost[a]);
      return dp;
    };
    auto dp = dfs3(dfs3, 0, -1);
    cout << max(dp[0], dp[1]) << '\n';
  }
}
