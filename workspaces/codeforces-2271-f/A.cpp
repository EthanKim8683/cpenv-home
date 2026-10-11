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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  mt19937 rng;
  if (argc > 1) {
    rng = mt19937(atoi(argv[1]));
  }

  int T;
  if (argc > 1) {
    T = 1;
  } else {
    cin >> T;
  }

  while (T--) {
    int N;
    if (argc > 1) {
      N = 200;
    } else {
      cin >> N;
    }

    vi A(N);
    if (argc > 1) {
      for (auto &e : A) {
        e = rng() % 3 + 1;
      }
    } else {
      for (auto &e : A) cin >> e;
    }

    pii peak = {0, -1};
    rep(i, 0, N) { chmax(peak, pii{A[i], i}); }

    vc<pii> stack1;
    rep(i, 0, peak.sd) {
      while (sz(stack1) > 0 and stack1.back().fs < A[i]) {
        stack1.pop_back();
      }
      if (sz(stack1) == 0 or stack1.back().fs != A[i]) {
        stack1.eb(A[i], 0);
      }
      stack1.back().sd++;
    }

    vc<pii> stack2;
    for (int i = N - 1; i > peak.sd; i--) {
      while (sz(stack2) > 0 and stack2.back().fs < A[i]) {
        stack2.pop_back();
      }
      if (sz(stack2) == 0 or stack2.back().fs != A[i]) {
        stack2.eb(A[i], 0);
      }
      stack2.back().sd++;
    }

    int x = -1;
    for (int i = 0, j = 0; i < sz(stack1) and j < sz(stack2);) {
      if (stack1[i].fs > stack2[j].fs) {
        i++;
      } else if (stack1[i].fs < stack2[j].fs) {
        j++;
      } else if (stack1[i].sd == 1 or stack2[j].sd == 1) {
        x = stack1[i].fs;
        break;
      } else {
        i++;
        j++;
      }
    }

    auto is_beautiful = [&](vi A) -> bool {
      vc<pii> stack;
      vi ps(N + 1, 0);
      rep(i, 0, N) {
        while (sz(stack) > 0 and stack.back().fs < A[i]) {
          stack.pop_back();
        }
        if (sz(stack) > 0 and stack.back().fs == A[i]) {
          ps[stack.back().sd] += 1;
          ps[i + 1] -= 1;
        }
        stack.eb(A[i], i);
      }
      rep(i, 0, N) { ps[i + 1] += ps[i]; }
      rep(i, 0, N) {
        if (ps[i] == 0) return false;
      }
      return true;
    };

    vc<pii> ans;
    auto check = [&](vc<pii> cand) -> bool {
      vi A2 = A;
      for (auto [i, x] : cand) {
        A2[i] = x;
      }
      if (is_beautiful(A2)) {
        ans = cand;
        return true;
      }
      return false;
    };

    if (check({})) goto TEST_OR_OUTPUT;
    if (check({{0, peak.fs}})) goto TEST_OR_OUTPUT;
    if (check({{N - 1, peak.fs}})) goto TEST_OR_OUTPUT;
    if (x != -1 and check({{peak.sd, x}})) goto TEST_OR_OUTPUT;
    assert(check({{0, peak.fs}, {N - 1, peak.fs}}));

  TEST_OR_OUTPUT:
    if (argc > 1) {
      if (sz(ans) < 2) continue;

      vi cand = A;
      sort(all(cand));
      cand.erase(unique(all(cand)), cand.end());

      bool found = false;
      rep(i, 0, N) {
        vi A2 = A;
        for (auto e : cand) {
          A2[i] = e;
          found = found or is_beautiful(A2);
        }
      }
      assert(!found);
    } else {
      cout << sz(ans) << '\n';
      for (auto [i, x] : ans) {
        cout << i + 1 << ' ' << x << '\n';
      }
    }
  }
}
