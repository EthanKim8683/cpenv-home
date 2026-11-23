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
    int N, M;
    cin >> N >> M;

    vc<tuple<int, int, int>> edges(M);
    for (auto &[u, v, l] : edges) {
      cin >> u >> v >> l;
      u--, v--, l--;
    }

    vc d(3, dsu(N));
    for (auto [u, v, l] : edges) {
      d[l].merge(u, v);
    }
    vc by_leader(3, vc<vi>(N));
    rep(i, 0, 3) {
      rep(j, 0, N) { by_leader[i][d[i].leader(j)].pb(j); }
    }

    for (auto r : by_leader[1]) {
      sort(all(r), [&](int a, int b) -> bool {
        return d[2].leader(a) < d[2].leader(b);
      });
      rep(i, 0, sz(r) - 1) {
        if (d[2].leader(r[i]) == d[2].leader(r[i + 1])) {
          d[0].merge(r[i], r[i + 1]);
        }
      }
    }

    vi ans;
    rep(i, 0, N) {
      if (d[0].leader(i) == d[0].leader(0)) {
        ans.pb(i);
      }
    }
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e + 1 << ' ';
    }
    cout << '\n';
  }
}
