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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

using ll = int;

const ll mod = (119 << 23) + 1, root = 62;  // = 998244353
ll modpow(ll b, ll e) {
  ll ans = 1;
  for (; e; b = b * b % mod, e /= 2)
    if (e & 1) ans = ans * b % mod;
  return ans;
}
// For p < 2^30 there is also e.g. 5 << 25, 7 << 26, 479 << 21
// and 483 << 21 (same root). The last two are > 10^9.
typedef vi vl;
void ntt(vl &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vl rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    ll z[] = {1, modpow(root, mod >> s)};
    rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % mod;
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        ll z = rt[j + k] * a[i + j + k] % mod, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? mod : 0);
        ai += (ai + z >= mod ? z - mod : z);
      }
}
vl conv(const vl &a, const vl &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = modpow(n, mod - 2);
  vl L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = (ll) L[i] * R[i] % mod * inv % mod;
  ntt(out);
  return {out.begin(), out.begin() + s};
}
signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, K;
  cin >> N >> K;

  vi T(N + 1);
  for (auto &e : T) cin >> e;

  vi P(N + 1);
  for (auto &e : P) cin >> e;

  vi facts(N + 1);
  facts[0] = 1;
  rep(i, 1, N + 1) { facts[i] = facts[i - 1] * i % MOD; }

  auto mod_pow = [&](int x, int y) -> int {
    int rv = 1;
    for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
      if (y & 1) (rv *= x) %= MOD;
    return rv;
  };

  auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

  auto shift = [&](vi v, int k) -> vi {
    if (k == 0) return v;
    vi a(N + 1), b(N + 1);
    rep(i, 0, N + 1) {
      a[i] = facts[i] * mod_pow(k, i) % MOD * v[i] % MOD;
      b[i] = mod_inv(facts[N - i]);
    }
    auto c = conv(a, b);
    vi rv(N + 1);
    rep(i, 0, N + 1) {
      rv[i] = mod_inv(facts[i] * mod_pow(k, i)) * c[N + i] % MOD;
    }
    return rv;
  };
  auto T2 = shift(T, (K + MOD) % MOD), P2 = shift(P, (-K + MOD) % MOD);

  vi ans(N + 1);
  rep(i, 0, N + 1) { ans[i] = (T2[i] + P2[i]) % MOD; }
  for (auto e : ans) {
    cout << e << ' ';
  }
}
