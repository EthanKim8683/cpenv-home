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

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  int M = 2;
  cout << M << endl;

  vc P(2, vi(N));
  rep(i, 0, N) { P[0][i] = (i + 1) % N; }
  P[1] = P[0];
  swap(P[1][0], P[1].back());

  for (auto r : P) {
    for (auto e : r) {
      cout << e + 1 << ' ';
    }
    cout << endl;
  }

  vi Q(N);
  cin >> Q[0];
  Q[0]--;
  if (Q[0] == -1) {
    exit(0);
  }
  rep(i, 1, N) {
    cin >> Q[i];
    Q[i]--;
  }

  vi Qinv(N);
  rep(i, 0, N) { Qinv[Q[i]] = i; }

  vi ans;
  auto apply = [&](vi &v, int a) -> void {
    vi v2(N);
    rep(i, 0, N) { v2[i] = v[P[a][i]]; }
    v = v2;
  };

  auto op = [&](int x, int d) -> void {
    int j = 0;
    rep(i, 0, 2 * N) {
      if (Qinv[0] == x and j < d) {
        ans.pb(1);
        apply(Qinv, 1);
        j++;
      } else {
        ans.pb(0);
        apply(Qinv, 0);
      }
    }
  };

  for (int i = N - 2; i >= 0; i--) {
    int d = 0;
    rep(j, i + 1, N) {
      if (Qinv[i] < Qinv[j]) break;
      d++;
    }
    op(Qinv[i], d);
  }

  vi R(N);
  iota(all(R), 0);
  for (auto e : ans) {
    apply(R, e);
  }
  assert(R == Q);

  cout << sz(ans) << ' ';
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << endl;
}
