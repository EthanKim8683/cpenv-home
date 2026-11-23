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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vc<string> grid(N + 1);
  for (auto &r : grid) {
    cin >> r;
    for (auto &e : r) {
      if (e == '+') {
        e = -1;
      } else {
        e = e - '0';
      }
    }
  }

  vi state;
  vc<vi> states;
  auto dfs = [&](auto self) -> void {
    if (sz(state) == 2 * N + 1) {
      states.pb(state);
      return;
    }

    if (sz(state) % 2 == 0) {
      vc<pii> stack;
      set<int> groups;
      for (int i = 0; i < sz(state); i += 2) {
        while (sz(stack) > 0 and state[i] <= stack.back().fs) {
          stack.pop_back();
        }
        stack.eb(state[i], i);
        groups.insert(state[i]);
      }
      for (auto [e, i] : stack) {
        if (i / 2 % 2 != sz(state) / 2 % 2) continue;
        state.pb(e);
        self(self);
        state.pop_back();
      }
      state.pb(sz(groups));
      self(self);
      state.pop_back();
    } else {
      rep(i, 0, 2) {
        state.pb(i);
        self(self);
        state.pop_back();
      }
    }
  };
  dfs(dfs);
  sort(all(states));

  auto encode = [&](vi state) -> int {
    return lower_bound(all(states), state) - states.begin();
  };

  auto decode = [&](int i) -> vi { return states[i]; };

  vc dp(N + 1, vi(sz(states), -1));
  rep(i, 0, 1 << N) {
    vi counts(N + 1, 0);
    rep(j, 0, N) {
      if (i >> j & 1) {
        counts[j + 1] += 1;
      } else {
        counts[j] += 1;
      }
    }

    bool ok = true;
    rep(j, 0, N + 1) {
      ok = ok and (grid[0][j] == -1 or counts[j] == grid[0][j]);
    }
    if (!ok) continue;

    vc<vi> adj(2 * (N + 1));
    ok = true;
    rep(j, 0, N) {
      if (i >> j & 1) {
        int a = j, b = N + 1 + j + 1;
        adj[a].pb(b);
        adj[b].pb(a);
      } else {
        int a = j + 1, b = N + 1 + j;
        adj[a].pb(b);
        adj[b].pb(a);
      }
    }

    vi leader(2 * (N + 1), -1);
    auto dfs = [&](auto self, int a, int p, int r) -> void {
      leader[a] = r;
      for (auto b : adj[a]) {
        if (b == p) continue;
        self(self, b, a, r);
      }
    };
    int r = 0;
    rep(i, 0, N + 1) {
      if (leader[i] != -1) continue;
      dfs(dfs, i, -1, r);
      r++;
    }

    vi state;
    state.pb(leader[0]);
    rep(j, 0, N) {
      state.pb(i >> j & 1);
      state.pb(leader[j + 1]);
    }
    dp[1][encode(state)] = -2;
  }
  rep(i, 1, N) {
    rep(j, 0, sz(states)) {
      if (dp[i][j] == -1) continue;

      vi state = decode(j);

      rep(k, 0, 1 << N) {
        vi counts(N + 1, 0);
        rep(l, 0, N) {
          if (state[1 + 2 * l] == 1) {
            counts[l] += 1;
          } else {
            counts[l + 1] += 1;
          }

          if (k >> l & 1) {
            counts[l + 1] += 1;
          } else {
            counts[l] += 1;
          }
        }

        bool ok = true;
        rep(l, 0, N + 1) {
          ok = ok and (grid[i][l] == -1 or counts[l] == grid[i][l]);
        }
        if (!ok) continue;

        vc<vi> adj(2 * (N + 1));
        ok = true;
        rep(l, 0, N) {
          if (k >> l & 1) {
            int a = l, b = N + 1 + state[2 * (l + 1)];
            adj[a].pb(b);
            adj[b].pb(a);
          } else {
            int a = l + 1, b = N + 1 + state[2 * l];
            adj[a].pb(b);
            adj[b].pb(a);
          }
        }

        vi leader(2 * (N + 1), -1);
        auto dfs = [&](auto self, int a, int p, int r) -> bool {
          if (leader[a] != -1) return false;
          leader[a] = r;
          for (auto b : adj[a]) {
            if (b == p) continue;
            if (!self(self, b, a, r)) return false;
          }
          return true;
        };
        ok = true;
        int r = 0;
        rep(i, 0, N + 1) {
          if (leader[i] != -1) continue;
          ok = ok and dfs(dfs, i, -1, r);
          r++;
        }
        if (!ok) continue;

        vi state2;
        state2.pb(leader[0]);
        rep(l, 0, N) {
          state2.pb(k >> l & 1);
          state2.pb(leader[l + 1]);
        }
        dp[i + 1][encode(state2)] = j;
      }
    }
  }
  int j0 = -1;
  rep(i, 0, sz(states)) {
    if (dp[N][i] == -1) continue;

    vi state = decode(i);

    vi counts(N + 1, 0);
    rep(j, 0, N) {
      if (state[1 + 2 * j] == 1) {
        counts[j] += 1;
      } else {
        counts[j + 1] += 1;
      }
    }

    bool ok = true;
    rep(j, 0, N + 1) {
      ok = ok and (grid[N][j] == -1 or counts[j] == grid[N][j]);
    }
    if (!ok) continue;

    j0 = i;
    break;
  }
  vc<string> ans;
  int j = j0;
  rep(i, 0, N) {
    vi state = decode(j);

    string e = "";
    rep(k, 0, N) { e += state[1 + 2 * k] == 1 ? '/' : '\\'; }
    ans.pb(e);

    j = dp[N - i][j];
  }
  reverse(all(ans));
  for (auto e : ans) {
    cout << e << '\n';
  }
}
