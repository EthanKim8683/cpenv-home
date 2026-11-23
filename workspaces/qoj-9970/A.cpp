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

const int MAXS = 1e6;
const int MOD1 = (1ll << 31) - 1;
const int MOD2 = 1e9 + 7;
const int INF = 1e18;

struct hashed {
  int n;
  string s;
  vi ps;
};

struct hasher {
  int b, m;
  vi pows, denoms;

  hasher(int _b, int _m) : b(_b % _m), m(_m) {
    auto mod_pow = [&](int x, int y) -> int {
      int rv = 1;
      for (x %= m; y; y >>= 1, (x *= x) %= m)
        if (y & 1) (rv *= x) %= m;
      return rv;
    };

    auto mod_inv = [&](int x) -> int { return mod_pow(x, m - 2); };

    pows = vi(2 * MAXS + 1);
    pows[0] = 1;
    rep(i, 1, 2 * MAXS + 1) { pows[i] = pows[i - 1] * b % m; }

    denoms = vi(2 * MAXS + 1);
    rep(i, 0, 2 * MAXS + 1) { denoms[i] = mod_inv(pows[i] - 1); }
  }

  hashed hash(string s) {
    int n = sz(s);
    vi ps(n + 1);
    ps[0] = 0;
    rep(i, 0, n) { ps[i + 1] = (ps[i] * b + s[i]) % m; }
    return {n, s, ps};
  }

  int get_hash(const hashed &h, int k) {
    // ((b^n)^r-1)/(b^n-1) * b^d * ps[n] + ps[d]
    int r = k / h.n, d = k % h.n;
    return ((pows[h.n * r] - 1) * denoms[h.n] % m * pows[d] % m * h.ps[h.n] +
            h.ps[d]) %
           m;
  }

  char get_char(const hashed &h, int k) { return h.s[k % h.n]; }

  int lcp(const hashed &h1, const hashed &h2) {
    int l = 0, r = 2 * MAXS;
    while (l < r) {
      int m = l + (r - l + 1) / 2;
      get_hash(h1, m) == get_hash(h2, m) ? l = m : r = m - 1;
    }
    if (l == 2 * MAXS) return INF;
    return l;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

// vc<int> v -> vc<T> v
// v[i] > v[st.back()] -> above(v[i], v[st.back()])
pair<int, vc<pii>> cartesian_tree(vc<int> v) {
  vc<pii> rv(sz(v), {-1, -1});
  vi st;
  rep(i, 0, sz(v)) {
    while (sz(st) and v[i] < v[st.back()]) {
      rv[i].fs = st.back();
      st.pop_back();
    }
    if (sz(st)) rv[st.back()].sd = i;
    st.pb(i);
  }
  return {st[0], rv};
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // use hashing to find lcp

  mt19937 rng(time(nullptr));
  int b1 = rng(), b2 = rng();

  int N;
  cin >> N;

  vc<string> S(N);
  for (auto &e : S) cin >> e;

  hasher hr1(b1, MOD1), hr2(b2, MOD2);
  vc<pair<hashed, hashed>> hd(N);
  rep(i, 0, N) { hd[i] = {hr1.hash(S[i]), hr2.hash(S[i])}; }

  sort(all(hd),
       [&](const pair<hashed, hashed> &a,
           const pair<hashed, hashed> &b) -> bool {
         int n = min(hr1.lcp(a.fs, b.fs), hr2.lcp(a.sd, b.sd));
         if (n == INF) return false;
         return hr1.get_char(a.fs, n) < hr1.get_char(b.fs, n);
       });

  vi lcps(N - 1);
  rep(i, 0, N - 1) {
    lcps[i] =
        min(hr1.lcp(hd[i].fs, hd[i + 1].fs), hr2.lcp(hd[i].sd, hd[i + 1].sd));
  }

  auto [r, adj] = cartesian_tree(lcps);
  int ans = 0;
  auto dfs = [&](auto self, int a, int l, int r) -> void {
    if (a == -1) return;
    auto [b1, b2] = adj[a];
    if (b2 != -1 and lcps[a] != INF and lcps[a] == lcps[b2]) {
      // cerr << l << ' ' << a << ' ' << b2 << ' ' << r << '\n';
      ans += (a - l) * (b2 - a) * (r - b2);
    }
    self(self, b1, l, a);
    self(self, b2, a, r);
  };
  dfs(dfs, r, -1, N - 1);
  cout << ans << '\n';
}
