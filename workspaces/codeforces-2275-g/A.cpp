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

    dsu d(N);
    sort(all(edges));
    vi weights;
    int sum = 0;
    for (auto [w, u, v] : edges) {
      if (d.same(u, v)) {
        sum += w;
        continue;
      }
      weights.pb(w);
      d.merge(u, v);
    }
    reverse(all(weights));
    vi ps(sz(weights) + 1);
    rep(i, 0, sz(weights)) { ps[i + 1] = ps[i] + weights[i]; }

    int n0 = -1;
    rep(i, 0, N) {
      if (i != d.leader(i)) continue;
      n0++;
    }

    while (Q--) {
      int x;
      cin >> x;

      auto profit = [&](int n) -> __int128 {
        return sum + ps[n] - (__int128) (n + n0) * (n + n0 + 1) / 2 * x;
      };
      auto dprofit = [&](int n) -> __int128 {
        return profit(n + 1) - profit(n);
      };
      int l = 0, r = sz(weights) - 1;
      while (l < r) {
        int m = l + (r - l) / 2;
        dprofit(m) < 0 ? r = m : l = m + 1;
      }
      cout << (int) max(profit(l), profit(sz(weights))) << ' ';
    }
    cout << '\n';
  }
}
