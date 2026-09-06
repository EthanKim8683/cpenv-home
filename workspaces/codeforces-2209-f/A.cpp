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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) cin >> e;

    vc<vi> adj(N);
    rep(i, 0, N - 1) {
      int u, v;
      cin >> u >> v;
      u--, v--;
      adj[u].pb(v);
      adj[v].pb(u);
    }

    vc<pii> furthest2(N);
    auto dfs4 = [&](auto self, int a, int p) -> void {
      furthest2[a] = {0, -a};
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a);
        auto fb = furthest2[b];
        chmax(furthest2[a], pii{fb.fs + 1, fb.sd});
      }
    };
    dfs4(dfs4, 0, -1);

    vc<map<int, int>> furthest(N);
    auto dfs5 = [&](auto self, int a, int p, pii fp) -> void {
      set<pii> fadj;
      fadj.insert(pii{0, -a});
      if (p != -1) {
        fadj.insert(fp);
      }
      for (auto b : adj[a]) {
        if (b == p) continue;
        auto fb = furthest2[b];
        fadj.insert(pii{fb.fs + 1, fb.sd});
      }

      for (auto b : adj[a]) {
        if (b == p) {
          fadj.erase(fp);
          furthest[a][b] = -fadj.rbegin()->sd;
          fadj.insert(fp);
        } else {
          auto fb = furthest2[b];
          fadj.erase(pii{fb.fs + 1, fb.sd});
          furthest[a][b] = -fadj.rbegin()->sd;
          fadj.insert(pii{fb.fs + 1, fb.sd});
        }
      }

      for (auto b : adj[a]) {
        if (b == p) continue;

        auto fb = furthest2[b];
        fadj.erase(pii{fb.fs + 1, fb.sd});
        auto fpb = *fadj.rbegin();
        fadj.insert(pii{fb.fs + 1, fb.sd});

        self(self, b, a, {fpb.fs + 1, fpb.sd});
      }
    };
    dfs5(dfs5, 0, -1, {-1, -1});

    vi sums(N, 0);
    auto dfs = [&](auto self, int a, int p) -> void {
      for (auto b : adj[a]) {
        if (b == p) continue;
        sums[furthest[b][a]] += A[b];
        self(self, b, a);
      }
    };
    dfs(dfs, 0, -1);

    vc<pii> cc;
    rep(i, 0, N) { cc.eb(sums[i], i); }
    auto dfs2 = [&](auto self, int a, int p) -> void {
      for (auto b : adj[a]) {
        if (b == p) continue;

        int c = furthest[b][a];
        sums[c] -= A[b];
        cc.eb(sums[c], c);

        int d = furthest[a][b];
        sums[d] += A[a];
        cc.eb(sums[d], d);

        self(self, b, a);

        sums[d] -= A[a];
        sums[c] += A[b];
      }
    };
    dfs2(dfs2, 0, -1);
    sort(all(cc));
    cc.erase(unique(all(cc)), cc.end());
    auto compress = [&](int a) -> int {
      return lower_bound(all(cc), pii{sums[a], a}) - cc.begin();
    };

    FT ft1(sz(cc)), ft2(sz(cc));
    auto add = [&](int i) -> void {
      int j = compress(i);
      ft1.update(j, sums[i]);
      ft2.update(j, 1);
    };
    auto remove = [&](int i) -> void {
      int j = compress(i);
      ft1.update(j, -sums[i]);
      ft2.update(j, -1);
    };
    auto query = [&]() -> int {
      return ft1.query(sz(cc)) -
             ft1.query(min(ft2.lower_bound(N - (K - 1)) + 1, sz(cc)));
    };
    rep(i, 0, N) { add(i); }

    int ans = 0;
    auto dfs3 = [&](auto self, int a, int p) -> void {
      chmax(ans, query() + A[a]);

      for (auto b : adj[a]) {
        if (b == p) continue;

        int c = furthest[b][a];
        remove(c);
        sums[c] -= A[b];
        add(c);

        int d = furthest[a][b];
        remove(d);
        sums[d] += A[a];
        add(d);

        self(self, b, a);

        remove(d);
        sums[d] -= A[a];
        add(d);

        remove(c);
        sums[c] += A[b];
        add(c);
      }
    };
    dfs3(dfs3, 0, -1);

    cout << ans << '\n';
  }
}
