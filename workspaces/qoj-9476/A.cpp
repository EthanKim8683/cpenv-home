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

int mod_pow(int x, int y) {
  int rv = 1;
  for (x %= MOD; y; y >>= 1, (x *= x) %= MOD)
    if (y & 1) (rv *= x) %= MOD;
  return rv;
}

int mod_inv(int x) { return mod_pow(x, MOD - 2); }

void ntt(vi &a) {
  int n = sz(a), L = 31 - __builtin_clz(n);
  static vi rt(2, 1);
  for (static int k = 2, s = 2; k < n; k *= 2, s++) {
    rt.resize(n);
    int z[] = {1, mod_pow(62, MOD >> s)};
    rep(i, k, 2 * k) rt[i] = rt[i / 2] * z[i & 1] % MOD;
  }
  vi rev(n);
  rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
  rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
  for (int k = 1; k < n; k *= 2)
    for (int i = 0; i < n; i += 2 * k) rep(j, 0, k) {
        int z = rt[j + k] * a[i + j + k] % MOD, &ai = a[i + j];
        a[i + j + k] = ai - z + (z > ai ? MOD : 0);
        ai += (ai + z >= MOD ? z - MOD : z);
      }
}
vi conv(const vi &a, const vi &b) {
  if (a.empty() || b.empty()) return {};
  int s = sz(a) + sz(b) - 1, B = 32 - __builtin_clz(s), n = 1 << B;
  int inv = mod_pow(n, MOD - 2);
  vi L(a), R(b), out(n);
  L.resize(n), R.resize(n);
  ntt(L), ntt(R);
  rep(i, 0, n) out[-i & (n - 1)] = L[i] * R[i] % MOD * inv % MOD;
  ntt(out);
  return {out.begin(), out.begin() + s};
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int H, W;
  cin >> H >> W;

  vi fact(H + W + 1);
  fact[0] = 1;
  rep(i, 1, H + W + 1) { fact[i] = fact[i - 1] * i % MOD; }

  // vi h1(H + 1), h2(H + 1), w1(W + 1), w2(W + 1);
  // rep(i, 0, H + 1) {
  //   h1[i] = mod_inv((i + 1) * fact[i]);
  //   h2[i] = mod_inv(fact[i]);
  // }
  // rep(i, 0, W + 1) {
  //   w1[i] = mod_inv(fact[i]);
  //   w2[i] = mod_inv(fact[i]);
  // }
  // vi h = conv(h1, h2), w = conv(w1, w2);
  // h.resize(H + 1);
  // w.resize(W + 1);

  // int hH = h.back(), wW = w.back();
  // h.pop_back();
  // w.pop_back();

  // vi hw = conv(h, w);
  // int ans = 0;
  // rep(i, 0, sz(hw)) { (ans += 2 * hw[i] % MOD * fact[i]) %= MOD; }
  // rep(i, 0, sz(w)) {
  //   (ans += hH * w[i] % MOD * fact[H + i] % MOD * (W - i + 1)) %= MOD;
  // }
  // rep(i, 0, sz(h)) {
  //   (ans += wW * h[i] % MOD * fact[W + i] % MOD * (H - i + 1)) %= MOD;
  // }
  // (ans += hH * wW % MOD * fact[H + W]) %= MOD;
  // cout << ans << '\n';

  int ans = 2;
  rep(h, 0, H) {
    rep(w, 0, W) {
      rep(k, 0, min(h, w) + 1) {
        int contrib = fact[h + w] *
                      mod_inv((k + 1) * fact[k] % MOD * fact[k] % MOD *
                              fact[w - k] % MOD * fact[h - k]) %
                      MOD;
        if (h < H - 1 and w < W - 1) {
          (ans += 2 * contrib) %= MOD;
        } else {
          (ans += (H - h) * (W - w) % MOD * contrib) %= MOD;
        }
      }
    }
  }
  cout << ans << '\n';
}
