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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N, M;
  cin >> N >> M;

  vi A(N);
  for (auto &e : A) cin >> e;

  map<int, vi> indices;
  rep(i, 0, N) { indices[A[i]].pb(i); }

  vc dist(N, vi(2, INF));
  deque<pii> q;
  auto push = [&](int a, int s, int d, int w) -> void {
    if (d + w >= dist[a][s]) return;
    dist[a][s] = d + w;
    if (w == 0) {
      q.emplace_front(a, s);
    } else {
      q.emplace_back(a, s);
    }
  };
  auto push_both = [&](int a, int d, int w) -> void {
    push(a, 0, d, w);
    push(a, 1, d, w);
  };
  for (auto e : indices.begin()->sd) {
    push_both(e, 0, 1);
  }
  while (sz(q) > 0) {
    auto [a, s] = q.front();
    q.pop_front();
    auto it = indices.upper_bound(A[a]);
    if (it == indices.end()) {
      cout << sz(indices) << ' ' << dist[a][s] << '\n';
      exit(0);
    }
    auto it2 = upper_bound(all(it->sd), a);
    if (s == 0) {
      if (it2 == it->sd.end()) {
        push_both(*it->sd.begin(), dist[a][s], 1);
        push_both(*prev(it->sd.end()), dist[a][s], 1);
      } else {
        push(*it2, 0, dist[a][s], 0);
      }
    } else {
      if (it2 == it->sd.begin()) {
        push_both(*it->sd.begin(), dist[a][s], 1);
        push_both(*prev(it->sd.end()), dist[a][s], 1);
      } else {
        push(*prev(it2), 1, dist[a][s], 0);
      }
    }
  }
}
