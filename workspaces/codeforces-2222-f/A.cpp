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

struct dsu {
 public:
  dsu() : _n(0) {}
  explicit dsu(int n) : _n(n), parent_or_size(n, -1) {}

  int merge(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    int x = leader(a), y = leader(b);
    if (x == y) return x;
    if (-parent_or_size[x] < -parent_or_size[y]) std::swap(x, y);
    parent_or_size[x] += parent_or_size[y];
    parent_or_size[y] = x;
    return x;
  }

  bool same(int a, int b) {
    assert(0 <= a && a < _n);
    assert(0 <= b && b < _n);
    return leader(a) == leader(b);
  }

  int leader(int a) {
    assert(0 <= a && a < _n);
    return _leader(a);
  }

  int size(int a) {
    assert(0 <= a && a < _n);
    return -parent_or_size[leader(a)];
  }

  std::vector<std::vector<int>> groups() {
    std::vector<int> leader_buf(_n), group_size(_n);
    for (int i = 0; i < _n; i++) {
      leader_buf[i] = leader(i);
      group_size[leader_buf[i]]++;
    }
    std::vector<std::vector<int>> result(_n);
    for (int i = 0; i < _n; i++) {
      result[i].reserve(group_size[i]);
    }
    for (int i = 0; i < _n; i++) {
      result[leader_buf[i]].push_back(i);
    }
    result.erase(
        std::remove_if(result.begin(), result.end(),
                       [&](const std::vector<int> &v) { return v.empty(); }),
        result.end());
    return result;
  }

 private:
  int _n;
  // root node: -1 * component size
  // otherwise: parent
  std::vector<int> parent_or_size;

  int _leader(int a) {
    if (parent_or_size[a] < 0) return a;
    return parent_or_size[a] = _leader(parent_or_size[a]);
  }
};

struct dsu_with_rollbacks {
 private:
  std::vector<int> root, _color, saves;
  std::vector<std::tuple<int, int, int, int>> history;

 public:
  dsu_with_rollbacks() {}
  dsu_with_rollbacks(int n) : root(n, -1), _color(n, -1), saves({0}) {}

  void set_color(int a, int c) { _color[leader(a)] = c; }

  int color(int a) { return _color[leader(a)]; }

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
    history.push_back({a, b, root[b], _color[a]});
    root[a] += root[b];
    root[b] = a;
    if (_color[a] == -1) {
      _color[a] = _color[b];
    }
    return a;
  }

  bool same(int a, int b) { return leader(a) == leader(b); }

  int size(int a) { return -root[leader(a)]; }

  void save() { saves.push_back(history.size()); }

  void rollback() {
    while ((int) history.size() > saves.back()) {
      auto [a, b, size, c] = history.back();
      history.pop_back();
      root[a] -= size;
      root[b] = size;
      _color[a] = c;
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
    int N, M, Q;
    cin >> N >> M >> Q;

    vc<tuple<int, int, int>> edges(M);
    for (auto &[w, u, v] : edges) {
      cin >> u >> v >> w;
      u--, v--;
    }
    sort(all(edges));

    vi C(Q);
    for (auto &e : C) {
      cin >> e;
      e--;
    }
    sort(all(C));
    C.erase(unique(all(C)), C.end());

    int Mceil = 1 << __lg(2 * M - 1);
    vc<vi> st(2 * Mceil);
    auto add = [&](int l, int r, int i) -> void {
      for (l += Mceil, r += Mceil; l < r; l >>= 1, r >>= 1) {
        if (l & 1) {
          st[l].pb(i);
          l++;
        }
        if (r & 1) {
          r--;
          st[r].pb(i);
        }
      }
    };
    rep(i, 0, M) {
      auto [w, u, v] = edges[i];
      add(0, w, i);
      add(w + 1, Mceil, i);
    }

    int ans = 0;
    dsu d(N);
    dsu_with_rollbacks dr(N);
    for (auto e : C) {
      dr.set_color(e, e);
    }
    int contrib = 0;
    auto merge = [&](int a, int b) -> void {
      int ac = dr.color(a), bc = dr.color(b);
      if (ac != -1 and bc != -1 and !d.same(ac, bc)) {
        d.merge(ac, bc);
        contrib += 1;
      }
      dr.merge(a, b);
    };
    auto dfs = [&](auto self, int i) -> void {
      dr.save();
      for (auto j : st[i]) {
        auto [w, u, v] = edges[j];
        merge(u, v);
      }
      if (i >= Mceil) {
        ans += (i - Mceil) * contrib;
        contrib = 0;
      } else {
        self(self, i << 1);
        self(self, i << 1 | 1);
      }
      dr.rollback();
    };
    dfs(dfs, 1);
    int count = 0;
    for (auto e : C) {
      if (d.leader(e) == e) {
        count += 1;
      }
    }
    if (count > 1) {
      cout << "-1\n";
      continue;
    }
    cout << ans << '\n';
  }
}
