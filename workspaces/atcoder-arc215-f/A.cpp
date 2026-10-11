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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

typedef complex<double> C;
typedef vc<double> vd;
void fft(vc<C> &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vc<complex<long double>> R(2, 1);
  static vc<C> rt(2, 1);  // (^ 10% faster if double)
  for (static int k = 2; k < n; k *= 2) {
    R.resize(n);
    rt.resize(n);
    auto x = polar(1.0L, acos(-1.0L) / k);
    rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  ///
        // include-line
        auto x = (double *) &rt[j + k],
             y = (double *) &a[i + j + k];  /// exclude-line
        C z(x[0] * y[0] - x[1] * y[1],
            x[0] * y[1] + x[1] * y[0]);  /// exclude-line
        a[i + j + k] = a[i + j] - z;
        a[i + j] += z;
      }
}
vd conv(const vd &a, const vd &b) {
  if (a.empty() || b.empty()) return {};
  vd res(sz(a) + sz(b) - 1);
  int L = 32 - __builtin_clz(sz(res)), n = 1 << L;
  vc<C> in(n), out(n);
  copy(all(a), begin(in));
  rep(i, 0, sz(b)) in[i].imag(b[i]);
  fft(in);
  for (C &x : in) x *= x;
  rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
  fft(out);
  rep(i, 0, sz(res)) res[i] = imag(out[i]) / (4 * n);
  return res;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vc<vi> adj(N);
  rep(i, 0, N - 1) {
    int a, b;
    cin >> a >> b;
    a--, b--;
    adj[a].pb(b);
    adj[b].pb(a);
  }

  vc<pii> furthest(N);
  auto dfs = [&](auto self, int a, int p) -> void {
    furthest[a] = {1, -1};
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a);
      chmax(furthest[a], pii{furthest[b].fs + 1, b});
    }
  };
  dfs(dfs, 0, -1);
  int a = 0;
  while (furthest[a].sd != -1) {
    a = furthest[a].sd;
  }
  dfs(dfs, a, -1);
  vi path;
  while (a != -1) {
    path.pb(a);
    a = furthest[a].sd;
  }
  int root = path[sz(path) / 2];

  auto solve = [&](int x) -> pii {
    dfs(dfs, root, -1);
    vi leaves;
    auto dfs2 = [&](auto self, int a, int p) -> bool {
      bool keep = furthest[a].fs >= x, empty = true;
      for (auto b : adj[a]) {
        if (b == p) continue;
        if (!self(self, b, a)) {
          empty = false;
        }
      }
      if (keep and empty) {
        leaves.pb(a);
      }
      return empty and !keep;
    };
    dfs2(dfs2, root, -1);
    if (sz(leaves) == 0) return {-2, -2};
    if (sz(leaves) == 1) return {leaves[0], -1};
    if (sz(leaves) == 2) return {leaves[0], leaves[1]};
    return {-1, -1};
  };

  auto check = [&](int x) -> bool { return solve(x) != pii{-1, -1}; };
  int l = 0, r = N;
  while (l < r) {
    int m = l + (r - l) / 2;
    check(m) ? r = m : l = m + 1;
  }
  auto [u, v] = solve(l);

  vi par(N), dist(N), size(N);
  auto dfs3 = [&](auto self, int a, int p, int d) -> void {
    par[a] = p;
    dist[a] = d;
    size[a] = 1;
    for (auto b : adj[a]) {
      if (b == p) continue;
      self(self, b, a, d + 1);
      size[a] += size[b];
    }
  };
  dfs3(dfs3, root, -1, 0);

  auto dfs4 = [&](auto self, int a, int ex, vi &counts) -> void {
    if (a == ex) return;
    counts[dist[a]] += 1;
    for (auto b : adj[a]) {
      if (b == par[a]) continue;
      self(self, b, ex, counts);
    }
  };

  if (u == root) {
    vi counts1(N, 0);
    dfs4(dfs4, root, -1, counts1);
    auto counts2 = conv({all(counts1)}, {all(counts1)});
    vi ans(N);
    rep(i, 0, N) { ans[i] = lround(counts2[i]); }
    for (auto b : adj[root]) {
      vi counts3(size[b] + 1);
      dfs4(dfs4, b, -1, counts3);
      auto counts4 = conv({all(counts3)}, {all(counts3)});
      rep(i, 0, min(sz(counts4), N)) { ans[i] -= lround(counts4[i]); }
    }
    rep(i, 1, N) { ans[i] /= 2; }
    for (auto e : ans) {
      cout << e << '\n';
    }
    exit(0);
  }

  vi counts1(N, 0), counts2(N, 0);
  if (v == -1) {
    int ex = u;
    while (par[ex] != root) {
      ex = par[ex];
    }
    dfs4(dfs4, u, -1, counts1);
    dfs4(dfs4, root, ex, counts2);
  } else {
    dfs4(dfs4, u, -1, counts1);
    dfs4(dfs4, v, -1, counts2);
  }
  auto ans = conv({all(counts1)}, {all(counts2)});
  rep(i, 0, N) { cout << lround(ans[i]) << '\n'; }
}
