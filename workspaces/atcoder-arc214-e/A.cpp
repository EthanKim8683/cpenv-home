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

  //

  // cost[i] = i - seen[P[i]][:i].sum()
  //
  // swap P[i] and P[j]:
  //
  // if k < min(i, j) or k > max(i, j)
  //   seen[P[k]][:k].sum() doesn't change -> cost[k] is unaffected
  // if P[k] < min(P[i], P[j]) or P[k] > max(P[i], P[j])
  //   seen[P[k]][:k].sum() doesn't change -> cost[k] is unaffected
  //
  // else
  //   seen[P[k]][:k] -= 1 -> cost[k] += 1
  //
  // i, j
  //   cost[i] = i - seen[P[j]][:i]
  //   cost[j] = j - seen[P[i]][:j]
  //
  // total cost = N(N-1)/2 - sum(seen[P[i]][:i].sum() for i in range(N))
  //
  // 1. find all P[i]
  // 2. if neighbors have odd distance, consider swapping
  //   - maintain "queries" array, (i, p, w, j)
  //     find w * seen[p][:i]
  //     if j == -1, add to base
  //     else add to delta[j]
  //   - if there are no such neighbors, no sol
  // 3. find min cost across all base and base + deltas

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi A(N);
    for (auto &e : A) {
      cin >> e;
      e--;
    }

    vi B(N);
    for (auto &e : B) {
      cin >> e;
      e--;
    }

    vc<vi> by_A(N);
    rep(i, 0, N) { by_A[A[i]].pb(i); }

    vi index(N), P(N);
    rep(i, 0, N) {
      P[by_A[B[i]][index[B[i]]]] = i;
      index[B[i]]++;
    }

    vc<vi> mst(2 * N);
    rep(i, 0, N) { mst[N + i].pb(P[i]); }
    for (int i = N - 1; i >= 1; i--) {
      merge(all(mst[i << 1]), all(mst[i << 1 | 1]), back_inserter(mst[i]));
    }
    auto sum = [&](int l1, int r1, int l2, int r2) -> int {
      int rv = 0;
      auto contrib = [&](int i) -> void {
        rv += lower_bound(all(mst[i]), r2) - lower_bound(all(mst[i]), l2);
      };
      for (l1 += N, r1 += N; l1 < r1; l1 >>= 1, r1 >>= 1) {
        if (l1 & 1) contrib(l1++);
        if (r1 & 1) contrib(--r1);
      }
      return rv;
    };

    vc<tuple<int, int, int, int>> queries;
    vi deltas;
    deltas.pb(0);
    rep(i, 0, N) {
      rep(j, 0, sz(by_A[i]) - 1) {
        int k = by_A[i][j], l = by_A[i][j + 1], m = sz(deltas);
        deltas.pb(sum(k + 1, l, P[k] + 1, P[l]));
        queries.eb(k, P[k], 1, m);
        queries.eb(l, P[l], 1, m);
        queries.eb(k, P[l], -1, m);
        queries.eb(l, P[k], -1, m);
      }
    }

    vi by_P(N);
    rep(i, 0, N) { by_P[P[i]] = i; }

    vc<vi> queries_by_p(N);
    rep(i, 0, sz(queries)) {
      auto [j, p, w, k] = queries[i];
      queries_by_p[p].pb(i);
    }

    FT ft(N);
    int base = N * (N - 1) / 2;
    rep(i, 0, N) {
      int j = by_P[i];
      base -= ft.query(j);
      for (auto k : queries_by_p[i]) {
        auto [l, p, w, m] = queries[k];
        deltas[m] += w * ft.query(l);
      }
      ft.update(j, 1);
    }

    int ans = INF;
    for (auto delta : deltas) {
      int ops = base + delta;
      if (ops == 0) {
        ans = 0;
        break;
      }
      int cost = (ops - 1) / K + 1;
      if (K % 2 == 0) {
        if ((cost * K - ops) % 2 != 0) continue;
        chmin(ans, cost);
      } else {
        if ((cost * K - ops) % 2 == 0) {
          chmin(ans, cost);
        } else {
          chmin(ans, cost + 1);
        }
      }
    }
    cout << (ans == INF ? -1 : ans) << '\n';
  }
}
