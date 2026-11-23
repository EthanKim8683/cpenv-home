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

const int LOGN = 18;
const int INF = 1e18;

template <class S, auto op, auto e>
struct sparse_table {
  int n;
  vc<vc<S>> d;
  sparse_table(const vc<S> &v) : n(sz(v)), d(__lg(n) + 1, vc<S>(n, e())) {
    copy(all(v), d[0].begin());
    rep(i, 1, sz(d)) rep(j, 0, n - (1 << i) + 1) d[i][j] =
        op(d[i - 1][j], d[i - 1][j + (1 << (i - 1))]);
  }
  S prod(int l, int r) {
    if (l >= r) return e();
    int i = __lg(r - l);
    return op(d[i][l], d[i][r - (1 << i)]);
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

    int t = 0;
    vi tin(N), tout(N), depth(N);
    auto dfs = [&](auto self, int a, int p, int d) -> void {
      tin[a] = t;
      t++;
      depth[a] = d;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, d + 1);
      }
      tout[a] = t;
    };
    dfs(dfs, 0, -1, 0);

    vi init(N);
    rep(i, 0, N) { init[tin[i]] = depth[i]; }

    using S = int;
    auto op = [&](S a, S b) -> S { return max(a, b); };
    auto e = [&]() -> S { return -INF; };
    sparse_table<S, op, e> st(init);

    vc anc(N, vc<tuple<int, int, int>>(LOGN + 1));
    auto dfs2 = [&](auto self, int a, int p) -> void {
      if (p == -1) {
        anc[a][0] = {a, -INF, 0};
      } else {
        anc[a][0] = {
          p,
          1 + max(st.prod(tin[p], tin[a]), st.prod(tout[a], tout[p])) -
              depth[p],
          1};
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
      }
    };
    dfs2(dfs2, 0, -1);
    rep(i, 1, LOGN + 1) {
      rep(j, 0, N) {
        auto [p1, d1, n1] = anc[j][i - 1];
        auto [p2, d2, n2] = anc[p1][i - 1];
        anc[j][i] = {p2, max(d1, n1 + d2), n1 + n2};
      }
    }

    int Q;
    cin >> Q;

    while (Q--) {
      int v, k;
      cin >> v >> k;
      v--;

      int d1 = st.prod(tin[v], tout[v]) - depth[v], n1 = 0;
      for (int i = LOGN; i >= 0; i--) {
        if ((1 << i) > k) continue;
        auto [p, d2, n2] = anc[v][i];
        tie(v, d1, n1) = tuple{p, max(d1, n1 + d2), n1 + n2};
        k -= 1 << i;
      }
      cout << d1 << ' ';
    }
    cout << '\n';
  }
}
