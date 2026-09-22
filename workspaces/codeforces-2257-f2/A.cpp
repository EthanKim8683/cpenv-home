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

const int INF = 1e18;
const int MAXX = 10;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // the difficulty of this problem is skipping multiple platforms at a time
  //
  // i think we can nicely solve this by storing by how far back the last jump
  // was (if we skip the final accounted for platform) or how far into the
  // current platform (if we visit the platform)
  //
  // this is probably enough, right?
  //
  // well we have to do this on both ends
  //
  // actually no
  //
  // is this passable? 10*10*10*20 = 2e4 * 1e4 = 2e8... not bad??
  //
  // technically, since there are few queries, we can compress segments?

  int N, Q, X;
  cin >> N >> Q >> X;

  vi D(N);
  for (auto &e : D) cin >> e;

  vi S(N);
  for (auto &e : S) cin >> e;

  vc<tuple<char, int, int>> queries(Q);
  for (auto &[t, a, b] : queries) {
    cin >> t >> a >> b;
    a--;
  }

  vi splits;
  splits.pb(0);
  splits.pb(N);
  for (auto [t, a, b] : queries) {
    if (t == '?') {
      splits.pb(a);
      splits.pb(b);
    } else {
      splits.pb(a);
      splits.pb(a + 1);
    }
  }
  sort(all(splits));
  splits.erase(unique(all(splits)), splits.end());

  vc<pii> ranges;
  rep(i, 0, sz(splits) - 1) { ranges.eb(splits[i], splits[i + 1]); }
  int M = sz(ranges);

  vi range(N + 1);
  range[N] = M;
  rep(i, 0, M) {
    auto [l, r] = ranges[i];
    rep(j, l, r) { range[j] = i; }
  }

  using Seg = array<int, MAXX * MAXX>;
  auto op = [&](Seg a, Seg b) -> Seg {
    Seg rv;
    rep(i, 0, X) {
      rep(j, 0, X) {
        auto &e = rv[i * X + j];
        e = INF;
        rep(k, 0, X) { chmin(e, a[i * X + k] + b[k * X + j]); }
      }
    }
    return rv;
  };
  auto e = [&]() -> Seg {
    Seg rv;
    fill(all(rv), INF);
    rep(i, 0, X) { rv[i * X + i] = 0; }
    return rv;
  };
  auto seg = [&](int d, int s) -> Seg {
    Seg rv;
    rep(i, 0, X) {
      rep(j, 0, X) {
        auto &e = rv[i * X + j];
        if (i >= d) {
          if (d + j == i) {
            e = 0;
          } else {
            e = INF;
          }
        } else {
          e = (d + j - i - 1) / X * s;
        }
      }
    }
    return rv;
  };
  vc<Seg> st(2 * M);
  rep(i, 0, M) {
    auto [l, r] = ranges[i];
    auto x = e();
    rep(j, l, r) { x = op(x, seg(D[j], S[j])); }
    st[M + i] = x;
  }
  for (int i = M - 1; i >= 1; i--) {
    st[i] = op(st[i << 1], st[i << 1 | 1]);
  }
  auto set = [&](int i, Seg x) -> void {
    for (st[i += M] = x; i >>= 1;) {
      st[i] = op(st[i << 1], st[i << 1 | 1]);
    }
  };
  auto prod = [&](int l, int r) -> Seg {
    auto lrv = e(), rrv = e();
    for (l += M, r += M; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lrv = op(lrv, st[l++]);
      if (r & 1) rrv = op(st[--r], rrv);
    }
    return op(lrv, rrv);
  };
  for (auto [t, a, b] : queries) {
    if (t == '1') {
      D[a] = b;
      int i = range[a];
      set(i, seg(D[a], S[a]));
    } else if (t == '2') {
      S[a] = b;
      int i = range[a];
      set(i, seg(D[a], S[a]));
    } else {
      int l = range[a], r = range[b];
      cout << prod(l, r)[X - 1] << '\n';
    }
  }
}
