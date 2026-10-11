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

  int N, M, C;
  cin >> N >> M >> C;

  vc<vi> people(M);
  for (auto &r : people) {
    int k;
    cin >> k;

    r.resize(k);
    for (auto &e : r) {
      cin >> e;
      e--;
    }
  }

  vc<vi> bands(N);
  rep(i, 0, M) {
    for (auto e : people[i]) {
      bands[e].pb(i);
    }
  }

  vi crowds(N, 0), faves(M, 0);
  auto add_person = [&](int i) -> void {
    for (auto e : people[i]) {
      crowds[e] += 1;
    }
  };
  auto add_band = [&](int i) -> void {
    for (auto e : bands[i]) {
      faves[e] += 1;
    }
  };
  rep(i, 0, M) { add_person(i); }
  rep(i, 0, N) { add_band(i); }

  queue<pii> q;
  auto nudge_person = [&](int i) -> void {
    if (faves[i] < 0) return;
    if (2 * faves[i] >= sz(people[i])) return;
    faves[i] = -1;
    q.emplace(0, i);
  };
  auto nudge_band = [&](int i) -> void {
    if (crowds[i] < 0) return;
    if (crowds[i] >= C) return;
    crowds[i] = -1;
    q.emplace(1, i);
  };
  rep(i, 0, M) { nudge_person(i); }
  rep(i, 0, N) { nudge_band(i); }
  auto remove_person = [&](int i) -> void {
    for (auto e : people[i]) {
      crowds[e] -= 1;
      nudge_band(e);
    }
  };
  auto remove_band = [&](int i) -> void {
    for (auto e : bands[i]) {
      faves[e] -= 1;
      nudge_person(e);
    }
  };
  while (sz(q) > 0) {
    auto [t, i] = q.front();
    q.pop();
    if (t == 0) {
      remove_person(i);
    } else {
      remove_band(i);
    }
  }
  vi ans;
  rep(i, 0, N) {
    if (crowds[i] < 0) continue;
    ans.pb(i);
  }
  if (sz(ans) == 0) {
    cout << "impossible\n";
    exit(0);
  }
  cout << "possible\n";
  cout << sz(ans) << '\n';
  for (auto e : ans) {
    cout << e + 1 << ' ';
  }
  cout << '\n';
}
