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

template <class S, auto add, auto cp, auto rb, auto cb>
struct offline_deletion {
  int n;
  vc<vc<S>> s;
  offline_deletion(int _n) : n(1 << __lg(2 * _n - 1)), s(n + _n) {}
  void apply(int l, int r, S t) {
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) s[l++].pb(t);
      if (r & 1) s[--r].pb(t);
    }
  }
  void dfs(int a = 1) {
    if (a >= sz(s)) return;
    cp();
    for (auto e : s[a]) add(e);
    a < n ? dfs(a << 1), dfs(a << 1 | 1) : cb(a - n);
    rb();
  }
};

struct dsu_with_rollbacks {
  vi d, s;
  vc<tuple<int, int, int>> h;
  dsu_with_rollbacks(int n) : d(n, -1) {}
  int leader(int a) { return d[a] < 0 ? a : leader(d[a]); }
  bool merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return 0;
    if (d[a] > d[b]) swap(a, b);
    h.eb(a, b, d[b]);
    d[a] += d[b], d[b] = a;
    return 1;
  }
  int size(int a) { return -d[a]; }
  void save() { s.pb(sz(h)); }
  void rollback() {
    while (sz(h) > s.back()) {
      auto [a, b, x] = h.back();
      h.pop_back();
      d[b] = x, d[a] -= d[b];
    }
    s.pop_back();
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

    vc<pii> ranges(M);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
      l--;
    }

    vc<tuple<int, int, int>> queries(Q);
    for (auto &[p, l, r] : queries) {
      cin >> p >> l >> r;
      p--, l--;
    }

    static dsu_with_rollbacks d(0);
    static int sum;
    static vi sum_history, ans;
    d = dsu_with_rollbacks(N + 1);
    sum = 0;
    sum_history = {};
    ans = vi(Q + 1);

    using S = pii;
    auto add = [&](S s) -> void {
      auto [l, r] = s;
      if (d.leader(l) == d.leader(r)) return;
      d.merge(l, r);
      sum++;
    };
    auto cp = [&]() -> void {
      d.save();
      sum_history.pb(sum);
    };
    auto rb = [&]() -> void {
      d.rollback();
      sum = sum_history.back();
      sum_history.pop_back();
    };
    auto cb = [&](int i) -> void { ans[i] = sum; };
    offline_deletion<S, add, cp, rb, cb> od(Q + 1);
    vi lefts(M, 0);
    rep(i, 0, Q) {
      auto [p, l, r] = queries[i];
      od.apply(lefts[p], i + 1, ranges[p]);
      ranges[p] = {l, r};
      lefts[p] = i + 1;
    }
    rep(i, 0, M) { od.apply(lefts[i], Q + 1, ranges[i]); }
    od.dfs();

    rep(i, 0, Q + 1) { cout << ans[i] << '\n'; }
  }
}
