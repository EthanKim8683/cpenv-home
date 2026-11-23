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

const int MAXH = 1e9;
const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  while (T--) {
    int N, K;
    cin >> N >> K;

    vi H(N);
    for (auto &e : H) cin >> e;

    vi order(N);
    iota(all(order), 0);
    sort(all(order), [&](int a, int b) -> bool { return H[a] > H[b]; });

    auto check = [&](int x) -> bool {
      vi H2(N, -INF);
      vc<pii> q;
      for (int i = 0, j = 0; i < N or j < sz(q);) {
        pii best = {-INF, -1};
        if (i < N and j < sz(q)) {
          int k = order[i];
          if (H[k] > q[j].fs) {
            best = {H[k], k};
            i++;
          } else {
            best = q[j];
            j++;
          }
        } else if (i < N) {
          int k = order[i];
          best = {H[k], k};
          i++;
        } else if (j < sz(q)) {
          best = q[j];
          j++;
        }
        auto [h, k] = best;
        if (h <= H2[k]) continue;
        H2[k] = h;
        q.eb(h - x, (k + N - 1) % N);
        q.eb(h - x, (k + 1) % N);
      }
      int sum = 0;
      rep(i, 0, N) { sum += H2[i] - H[i]; }
      return sum <= K;
    };
    int l = 0, r = MAXH;
    while (l < r) {
      int m = l + (r - l) / 2;
      check(m) ? r = m : l = m + 1;
    }
    cout << l << '\n';
  }
}
