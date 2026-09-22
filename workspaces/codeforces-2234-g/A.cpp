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

  // at most nlogn losing states
  //
  // process right to left, top to bottom
  //
  // for each index i, for each power p,
  // if win, p -= A[i] + 1
  // if lose, set earliest preceding loss for power p to i - (p + 1) and p--
  //
  // well not exactly, but close enough
  //
  // find first chunk of losses of size > A[i]
  // we can use a set and merge as we get more losses

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    // vc win(N + 1, vc<bool>(N + 1, false));
    // for (int i = N; i >= 0; i--) {
    //   for (int p = N; p >= 1; p--) {
    //     bool lose = true;
    //     if (i < N) {
    //       rep(j, p, min(p + A[i], N) + 1) { lose = lose and !win[i][j]; }
    //     }
    //     if (lose) {
    //       rep(j, max(i - p, 0ll), i) { win[j][p] = true; }
    //     }
    //     if (i == 0 and p == 1) {
    //       cout << (lose ? 2 : 1) << '\n';
    //     }
    //   }
    // }

    set<pii> by_range;
    set<tuple<int, pii>> by_size;
    auto add = [&](pii x) -> void {
      if (x.fs == x.sd) return;
      by_range.emplace(x);
      by_size.emplace(x.sd - x.fs, x);
    };
    auto remove = [&](pii x) -> void {
      by_range.erase(x);
      by_size.erase(pair{x.sd - x.fs, x});
    };
    pii nil = {-1, -1};
    auto find = [&](int x) -> pii {
      auto it = by_range.upper_bound(pii{x, N + 1});
      if (it == by_range.begin()) return nil;
      if (prev(it)->sd <= x) return nil;
      return *prev(it);
    };
    add({0, N + 1});

    vi coverage(N + 1, 0);
    vc<vi> by_left(N + 1);
    auto cover = [&](int i, int l) -> void {
      if (coverage[i] == 0) {
        auto [l2, r2] = find(i);
        remove(pii{l2, r2});
        add(pii{l2, i});
        add(pii{i + 1, r2});
      }
      coverage[i]++;
      if (l >= 0) {
        by_left[l].pb(i);
      }
    };
    auto uncover = [&](int l) -> void {
      for (auto i : by_left[l]) {
        coverage[i]--;
        if (coverage[i] == 0) {
          int l2 = i, r2 = i + 1;
          auto lrange = find(i - 1);
          if (lrange != nil) {
            remove(lrange);
            l2 = lrange.fs;
          }
          auto rrange = find(i + 1);
          if (rrange != nil) {
            remove(rrange);
            r2 = rrange.sd;
          }
          add(pii{l2, r2});
        }
      }
    };
    bool ans = true;
    for (int i = N; i >= 0; i--) {
      vc<pii> ranges;
      if (i < N) {
        for (auto it = by_size.rbegin(); it != by_size.rend(); it++) {
          auto [size, range] = *it;
          if (size <= A[i]) break;
          ranges.eb(range.fs, range.sd - A[i]);
        }
      } else {
        ranges.eb(0, N + 1);
      }

      for (auto [l, r] : ranges) {
        rep(j, l, r) {
          if (i == 0 and j == 1) {
            ans = false;
          }
          cover(j, i - j);
        }
      }
      uncover(i);
    }
    cout << (ans ? 1 : 2) << '\n';
  }
}
