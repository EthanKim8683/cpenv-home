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

struct dsu {
  vi d;
  dsu(int n) : d(n, -1) {}
  int leader(int a) { return d[a] < 0 ? a : d[a] = leader(d[a]); }
  bool merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return 0;
    if (d[a] > d[b]) swap(a, b);
    d[a] += d[b], d[b] = a;
    return 1;
  }
  int size(int a) { return -d[a]; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

int mod_pow(int a, int b, int m = MOD) {
  int rv = 1;
  for (a %= m; b; b >>= 1, (a *= a) %= m)
    if (b & 1) (rv *= a) %= m;
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  mt19937_64 rng(time(nullptr));

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<string> A(N);
    for (auto &e : A) cin >> e;

    auto is_inside = [&](int i, int j) -> int {
      return 0 <= i and i < N and 0 <= j and j < M;
    };
    vc seen1(N, vc<bool>(M, false)), seen2(N, vc<bool>(M, false));
    auto dfs1 = [&](auto self, int i, int j) -> void {
      if (!is_inside(i, j)) return;
      if (A[i][j] == '0') return;
      if (seen1[i][j]) return;
      seen1[i][j] = true;
      self(self, i + 1, j);
      self(self, i, j + 1);
    };
    dfs1(dfs1, 0, 0);
    auto dfs2 = [&](auto self, int i, int j) -> void {
      if (!is_inside(i, j)) return;
      if (A[i][j] == '0') return;
      if (seen2[i][j]) return;
      seen2[i][j] = true;
      self(self, i - 1, j);
      self(self, i, j - 1);
    };
    dfs2(dfs2, N - 1, M - 1);

    vc hash(N, vc<unsigned int>(M, 0));
    queue<pii> q;
    auto is_reachable = [&](int i, int j) -> bool {
      return is_inside(i, j) and seen1[i][j] and seen2[i][j];
    };
    auto push = [&](int i, int j, unsigned int h) -> void {
      if (!is_reachable(i, j)) return;
      hash[i][j] ^= h;
      if (hash[i][j] == h) {
        q.emplace(i, j);
      }
    };
    push(0, 0, rng());
    while (sz(q) > 0) {
      auto [i, j] = q.front();
      q.pop();
      if (is_reachable(i + 1, j) and is_reachable(i, j + 1)) {
        int h = rng();
        push(i + 1, j, h);
        push(i, j + 1, h ^ hash[i][j]);
      } else if (is_reachable(i + 1, j)) {
        push(i + 1, j, hash[i][j]);
      } else if (is_reachable(i, j + 1)) {
        push(i, j + 1, hash[i][j]);
      }
    }
    auto encode = [&](int i, int j) -> int { return i * M + j; };
    dsu d(N * M);
    map<int, int> leaders;
    rep(i, 0, N) {
      rep(j, 0, M) {
        if (!leaders.contains(hash[i][j])) {
          leaders[hash[i][j]] = encode(i, j);
        } else {
          d.merge(leaders[hash[i][j]], encode(i, j));
        }
      }
    }
    int ans = 0;
    rep(i, 0, N * M) {
      if (d.leader(i) != i) continue;
      (ans += mod_pow(2, d.size(i)) + MOD - 1) %= MOD;
    }
    cout << ans << '\n';
  }
}
