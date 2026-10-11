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

struct dsu_with_rollbacks {
 private:
  std::vector<int> root, saves;
  std::vector<std::tuple<int, int, int>> history;

 public:
  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) : root(n, -1), saves({0}) {}

  // https://codeforces.com/blog/entry/90340?#comment-787571
  // O(\log(N))
  int leader(int a) {
    if (root[a] < 0) return a;
    return leader(root[a]);
  }

  int merge(int a, int b) {
    if ((a = leader(a)) == (b = leader(b))) return a;
    if (root[a] > root[b]) {
      std::swap(a, b);
    }
    history.push_back({a, b, root[b]});
    root[a] += root[b];
    root[b] = a;
    return a;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -root[leader(a)]; }

  void save() { saves.push_back(history.size()); }

  void rollback() {
    while ((int) history.size() > saves.back()) {
      auto [a, b, size] = history.back();
      history.pop_back();
      root[a] -= size;
      root[b] = size;
    }
    saves.pop_back();
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<pii> edges(M);
    for (auto &[u, v] : edges) {
      cin >> u >> v;
      u--, v--;
    }

    vc<vc<pii>> adj(N);
    rep(i, 0, M) {
      auto [u, v] = edges[i];
      adj[u].eb(v, i);
      adj[v].eb(u, i);
    }

    vc<vi> queries;
    vi stack;
    vc<bool> seen(N, false);
    rep(i, 0, M) {
      auto [s, t] = edges[i];

      vi dist(N, INF);
      queue<int> q;
      auto push = [&](int a, int d) -> void {
        if (d >= dist[a]) return;
        dist[a] = d;
        q.push(a);
      };
      push(t, 0);
      while (sz(q) > 0) {
        int a = q.front();
        q.pop();
        for (auto [b, j] : adj[a]) {
          if (j == i) continue;
          push(b, dist[a] + 1);
        }
      }

      auto dfs = [&](auto self, int a) -> void {
        if (seen[a]) return;
        seen[a] = true;
        if (a == t) {
          queries.pb(stack);
        }
        for (auto [b, j] : adj[a]) {
          if (j == i) continue;
          if (sz(stack) + dist[b] > M - (N - 1)) continue;
          stack.pb(j);
          self(self, b);
          stack.pop_back();
        }
        seen[a] = false;
      };
      stack.pb(i);
      dfs(dfs, s);
      stack.pop_back();
    }

    int m = sz(queries);
    if (m == 0) {
      cout << "NO\n";
      continue;
    }

    int m2 = 1 << __lg(2 * m - 1);
    vc<vi> st(2 * m2);
    auto apply = [&](int l, int r, int x) -> void {
      for (l += m2, r += m2; l < r; l >>= 1, r >>= 1) {
        if (l & 1) st[l++].pb(x);
        if (r & 1) st[--r].pb(x);
      }
    };

    set<int> removed;
    rep(i, 0, M) { removed.insert(i); }
    vi lefts(M);
    rep(i, 0, m) {
      set<int> remove(all(queries[i]));
      for (auto e : removed) {
        if (remove.contains(e)) continue;
        lefts[e] = i;
      }
      for (auto e : remove) {
        if (removed.contains(e)) continue;
        apply(lefts[e], i, e);
      }
      removed = remove;
    }
    rep(i, 0, M) {
      if (removed.contains(i)) continue;
      apply(lefts[i], m, i);
    }

    bool found = false;
    dsu_with_rollbacks dr(N);
    int cc = N;
    auto dfs2 = [&](auto self, int a, int l, int r) -> void {
      dr.save();
      int saved_cc = cc;
      for (auto e : st[a]) {
        auto [u, v] = edges[e];
        if (dr.same(u, v)) continue;
        dr.merge(u, v);
        cc -= 1;
      }

      if (a >= m2) {
        if (cc == 1) {
          found = true;
          return;
        }
      } else {
        int m = l + (r - l) / 2;
        self(self, a << 1, l, m);
        if (found) return;
        self(self, a << 1 | 1, m, r);
        if (found) return;
      }

      dr.rollback();
      cc = saved_cc;
    };
    dfs2(dfs2, 1, 0, m2);
    cout << (found ? "YES" : "NO") << '\n';
  }
}
