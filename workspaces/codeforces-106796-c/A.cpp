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

// https://jilljenn.github.io/tryalgo/_modules/tryalgo/union_rectangles.html#union_rectangles
template <class S, class T>
struct cover_query {
 private:
  struct seg {
    T c;
    S s, w;
  };

  int n;
  std::vector<seg> data;

 public:
  cover_query() {}
  cover_query(const std::vector<S> &l)
      : n(1 << std::__lg(2 * l.size() - 1)), data(2 * n, {0, 0, 0}) {
    for (int i = 0; i < l.size(); i++) {
      data[n + i].w = l[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i].w = data[i << 1].w + data[i << 1 | 1].w;
    }
  }
  cover_query(int _n) : cover_query(std::vector<S>(_n, 1)) {}

  S cover() { return data[1].s; }

  void add(int l, int r, T dc) {
    auto dfs = [&](auto self, int i, int sl, int sr) -> void {
      if (sr <= l or r <= sl) return;
      if (l <= sl and sr <= r) {
        data[i].c += dc;
      } else {
        int sm = sl + (sr - sl) / 2;
        self(self, i << 1, sl, sm);
        self(self, i << 1 | 1, sm, sr);
      }
      if (data[i].c == 0) {
        if (i >= n) {
          data[i].s = 0;
        } else {
          data[i].s = data[i << 1].s + data[i << 1 | 1].s;
        }
      } else {
        data[i].s = data[i].w;
      }
    };
    dfs(dfs, 1, 0, n);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, K;
  cin >> N >> K;

  vc<vc<pii>> adj(N);
  rep(i, 0, N) {
    int u, v, w;
    cin >> u >> v >> w;
    u--, v--;
    adj[u].eb(v, w);
    adj[v].eb(u, w);
  }

  vc<pii> pairs(K);
  for (auto &[a, b] : pairs) {
    cin >> a >> b;
    a--, b--;
  }

  // find cycle
  vi color(N, 0), cycle, weights;
  auto dfs = [&](auto self, int a, int p) -> int {
    if (color[a] == 1) {
      // other end of cycle is found!
      return a;
    } else if (color[a] == 2) {
      return -1;
    }
    color[a] = 1;

    for (auto [b, w] : adj[a]) {
      if (b == p) continue;
      int c = self(self, b, a);

      // found other end?
      if (c != -1) {
        // a -> b info
        cycle.pb(a);
        weights.pb(w);

        // close off cycle
        if (c == a) return -1;

        return c;
      }
    }

    color[a] = 2;
    return -1;
  };
  dfs(dfs, 0, -1);
  reverse(all(cycle));
  reverse(all(weights));

  vi index(N, -1);
  rep(i, 0, sz(cycle)) { index[cycle[i]] = i; }

  // cut cycle edges to make a bunch of trees rooted at cycle nodes
  vc<vc<pii>> adj2(N);
  vi root(N, -1);
  auto dfs2 = [&](auto self, int a, int p, int r) -> void {
    root[a] = r;
    for (auto [b, w] : adj[a]) {
      if (b == p) continue;
      if (index[b] != -1) continue;
      adj2[a].eb(b, w);
      self(self, b, a, r);
    }
  };
  for (auto e : cycle) {
    dfs2(dfs2, e, -1, e);
  }

  // create lca stuff
  vc anc(N, vi(LOGN));
  vi tin(N), tout(N);
  int t = 0;
  auto dfs3 = [&](auto self, int a, int p) -> void {
    tin[a] = t;
    t++;
    anc[a][0] = p;
    for (auto [b, w] : adj2[a]) {
      if (b == p) continue;
      self(self, b, a);
    }
    tout[a] = t;
  };
  for (auto e : cycle) {
    dfs3(dfs3, e, e);
  }
  rep(i, 1, LOGN) {
    rep(j, 0, N) { anc[j][i] = anc[anc[j][i - 1]][i - 1]; }
  }
  auto is_anc = [&](int a, int b) -> bool {
    return tin[a] <= tin[b] and tout[b] <= tout[a];
  };
  auto lca = [&](int a, int b) -> int {
    if (is_anc(a, b)) return a;
    if (is_anc(b, a)) return b;
    for (int i = LOGN - 1; i >= 0; i--) {
      if (!is_anc(anc[a][i], b)) {
        a = anc[a][i];
      }
    }
    return anc[a][0];
  };

  // for (auto e : cycle) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';

  // process pairs
  vi ps(N, 0);
  vc<pii> ranges;
  for (auto [a, b] : pairs) {
    if (root[a] == root[b]) {
      // same subtree in cycle-removed forest
      ps[a] += 1;
      ps[b] += 1;
      ps[lca(a, b)] -= 2;
    } else {
      // different subtree, so add range
      int l = index[root[a]], r = index[root[b]];
      if (l > r) {
        swap(l, r);
      }
      // cerr << a << ' ' << b << ": " << l << ' ' << r << '\n';
      ranges.eb(l, r);
      ps[a] += 1;
      ps[b] += 1;
    }
  }

  // handle same-subtree pairs
  int fixed = 0;
  auto dfs4 = [&](auto self, int a) -> void {
    for (auto [b, w] : adj2[a]) {
      self(self, b);
      if (ps[b] > 0) {
        fixed += w;
        ps[a] += ps[b];
      }
    }
  };
  for (auto e : cycle) {
    dfs4(dfs4, e);
  }

  // same-subtree pairs handling seems ok
  // range building seems ok

  // plan contributions at range start/end
  vc<vc<tuple<int, int, int>>> contribs(sz(cycle));
  for (auto [l, r] : ranges) {
    contribs[0].eb(l, r, 1);
    contribs[l].eb(l, r, -1);
    contribs[l].eb(0, l, 1);
    contribs[l].eb(r, sz(cycle), 1);
    contribs[r].eb(0, l, -1);
    contribs[r].eb(r, sz(cycle), -1);
    contribs[r].eb(l, r, 1);
  }

  // check cover for each removed edge
  cover_query<int, int> cq(weights);
  int best = accumulate(all(weights), 0ll);
  rep(i, 0, sz(cycle)) {  // i is edge index
    for (auto [l, r, d] : contribs[i]) {
      cq.add(l, r, d);
    }
    chmin(best, cq.cover());
  }
  cout << fixed + best << '\n';
}
