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

const int MAXA = 2e5;
const int MOD1 = (1ll << 31) - 1;
const int MOD2 = 1e9 + 7;
const int LOGN = 19;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

// vc<int> v -> vc<T> v
// v[i] > v[st.back()] -> above(v[i], v[st.back()])
pair<int, vc<pii>> cartesian_tree(vc<int> v) {
  vc<pii> rv(sz(v), {-1, -1});
  vi st;
  rep(i, 0, sz(v)) {
    while (sz(st) and v[i] > v[st.back()]) {
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

  //

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  auto add = [&](pii a, pii b) -> pii {
    return {(a.fs + b.fs) % MOD1, (a.sd + b.sd) % MOD2};
  };

  auto sub = [&](pii a, pii b) -> pii {
    return {(a.fs + MOD1 - b.fs) % MOD1, (a.sd + MOD2 - b.sd) % MOD2};
  };

  auto mul = [&](pii a, int b) -> pii {
    return {a.fs * b % MOD1, a.sd * b % MOD2};
  };

  vc<pii> pows(MAXA + LOGN + 2);
  pows[0] = {1, 1};
  rep(i, 0, MAXA + LOGN + 1) { pows[i + 1] = mul(pows[i], 2); }

  vc<pii> ps(N + 1);
  ps[0] = {0, 0};
  rep(i, 0, N) { ps[i + 1] = add(ps[i], pows[A[i]]); }

  int ans = 0;
  vc<set<pii>> seen(N + 1);
  auto [r, adj] = cartesian_tree(A);
  auto dfs = [&](auto self, int m, int l, int r) -> int {
    if (m == -1) {
      seen[l].insert(ps[l]);
      return l;
    }

    auto [f, s] = adj[m];
    f = self(self, f, l, m);
    s = self(self, s, m + 1, r);

    if (m - l < r - (m + 1)) {
      seen[f].clear();
      rep(j, l, m + 1) {
        // s - f = pow
        // s = pow + f
        rep(i, 0, LOGN) {
          if (seen[s].contains(add(pows[A[m] + i], ps[j]))) {
            ans += 1;
          }
        }
      }
      rep(j, l, m + 1) { seen[s].insert(ps[j]); }
      return s;
    } else {
      seen[s].clear();
      rep(j, m + 1, r + 1) {
        rep(i, 0, LOGN) {
          // s - f = pow
          // f = s - pow
          if (seen[f].contains(sub(ps[j], pows[A[m] + i]))) {
            ans += 1;
          }
        }
      }
      rep(j, m + 1, r + 1) { seen[f].insert(ps[j]); }
      return f;
    }
  };
  dfs(dfs, r, 0, N);
  cout << ans << '\n';
}
