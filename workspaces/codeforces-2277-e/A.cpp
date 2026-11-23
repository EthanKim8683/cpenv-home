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

  //

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    auto query = [&](int x, vi p) -> int {
      cout << "? " << x + 1 << ' ';
      for (auto e : p) {
        cout << ' ' << e;
      }
      cout << endl;
      int rv;
      cin >> rv;
      return rv;
    };

    auto answer = [&](vc<pii> ans) -> void {
      cout << "!\n";
      for (auto [u, v] : ans) {
        cout << u + 1 << ' ' << v + 1 << '\n';
      }
      cout.flush();
    };

    auto fill = [&](vi p) -> vi {
      set<int> s;
      rep(i, 1, N + 1) { s.insert(i); }
      for (auto e : p) {
        if (e == -1) continue;
        s.erase(e);
      }

      rep(i, 0, N) {
        if (p[i] != -1) continue;
        p[i] = *s.begin();
        s.erase(s.begin());
      }
      return p;
    };

    vi sizes(N);
    sizes[0] = N;
    rep(i, 1, N) {
      vi p(N, -1);
      p[0] = N - 1;
      p[i] = N;
      p = fill(p);
      sizes[i] = query(0, p) - N * (N - 1);
    }

    vi order(N);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return sizes[a] > sizes[b]; });

    int prev_sum = N * N;
    vc<pii> ans;
    rep(i, 1, N) {
      vi p(N, -1);
      rep(j, 0, i) {
        int b = order[j];
        p[b] = N - i + j;
      }
      int a = order[i];
      p[a] = N;
      p = fill(p);
      int sum = query(0, p);
      ans.eb(order[i - (sum - (prev_sum - N)) / sizes[a]], a);
      prev_sum = sum;
    }
    answer(ans);
  }
}
