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

const int MOD1 = (1ll << 31) - 1;
const int MOD2 = 1e9 + 7;
const int INF = 1e18;

struct hasher {
  int n, mod;
  vi ps, pows;

  hasher(int _n, int m, int base, int _mod)
      : n(_n), mod(_mod), ps(n + 1, 0), pows(m + 1) {
    base %= mod;
    pows[0] = 1;
    rep(i, 1, m + 1) { pows[i] = pows[i - 1] * base % mod; }
  }

  void add(int l, int r, int i) {
    (ps[l] += pows[i]) %= mod;
    (ps[r] += mod - pows[i]) %= mod;
  }

  void build() {
    rep(i, 0, n) { (ps[i + 1] += ps[i]) %= mod; }
  }

  int get(int i) { return ps[i]; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // read editorial
  //
  // i think i need to slow down a bit to fully understand the problem before
  // jumping to how to solve it

  mt19937 rng(time(nullptr));
  int base1 = rng(), base2 = rng();

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    vc<pii> ranges(M);
    for (auto &[l, r] : ranges) {
      cin >> l >> r;
      l--;
    }

    hasher h1(N, M, base1, MOD1), h2(N, M, base2, MOD2);
    rep(i, 0, M) {
      auto [l, r] = ranges[i];
      h1.add(l, r, i);
      h2.add(l, r, i);
    }
    h1.build();
    h2.build();

    vc<pii> ranges2;
    map<pii, int> seen;
    pair<int, pii> key1 = {INF, {}}, key2 = {-INF, {}};
    rep(i, 0, N) {
      pii key = {h1.get(i), h2.get(i)};
      if (seen.contains(key)) {
        int j = seen[key];
        ranges2.eb(j, i);
        chmin(key1, pair{j, key});
        chmax(key2, pair{i, key});
      }
      seen[key] = i;
    }

    if (sz(ranges2) == 0) {
      cout << "0\n";
      continue;
    }

    sort(all(ranges2), [&](pii a, pii b) -> bool {
      auto key = [&](pii x) -> pii { return {x.sd, -x.fs}; };
      return key(a) < key(b);
    });
    vc<pii> ranges3;
    int lmax = -INF;
    for (auto [l, r] : ranges2) {
      if (l <= lmax) continue;
      ranges3.eb(l, r);
      lmax = l;
    }

    vi splits;
    if (sz(ranges3) % 2 == 0) {
      if (key1.sd == key2.sd) {
        splits.pb(0);
        for (auto [l, r] : ranges3) {
          splits.pb(l + 1);
        }
        splits.pb(N);
      } else {
        for (auto [l, r] : ranges3) {
          splits.pb(l + 1);
        }
      }
    } else {
      splits.pb(0);
      for (auto [l, r] : ranges3) {
        splits.pb(l + 1);
      }
    }

    vc<pii> ans;
    rep(i, 0, sz(splits) / 2) { ans.eb(splits[i], splits[sz(splits) / 2 + i]); }
    cout << sz(ans) << '\n';
    for (auto [l, r] : ans) {
      cout << l + 1 << ' ' << r << '\n';
    }

    // hasher h3(N, M + sz(ans), base1, MOD1), h4(N, M + sz(ans), base2, MOD2);
    // rep(i, 0, M) {
    //   auto [l, r] = ranges[i];
    //   h3.add(l, r, i);
    //   h4.add(l, r, i);
    // }
    // rep(i, 0, sz(ans)) {
    //   auto [l, r] = ans[i];
    //   h3.add(l, r, M + i);
    //   h4.add(l, r, M + i);
    // }
    // h3.build();
    // h4.build();
    // set<pii> hashes;
    // rep(i, 0, N) { hashes.insert({h3.get(i), h4.get(i)}); }
    // assert(sz(hashes) == N);
  }
}
