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

  vc<string> S(3);
  for (auto &e : S) cin >> e;

  auto get_indices = [&](string a) -> vi {
    vi rv;
    rep(i, 0, sz(a)) {
      if (a[i] == '1') {
        rv.pb(i);
      }
    }
    return rv;
  };

  vc<vi> indices(3);
  rep(i, 0, 3) { indices[i] = get_indices(S[i]); }

  int dist = 0;
  string ans(2 * N, '0');
  rep(i, 0, N) {
    vi indices2;
    rep(j, 0, 3) { indices2.pb(indices[j][i]); }
    sort(all(indices2));
    dist += indices2[1] - indices2[0];
    dist += indices2[2] - indices2[1];
    ans[indices2[1]] = '1';
  }
  cout << dist << '\n' << ans << '\n';
}
