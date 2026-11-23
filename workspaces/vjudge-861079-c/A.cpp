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

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  vi order(N);
  iota(all(order), 0);
  sort(all(order), [&](int a, int b) -> bool { return A[a] > A[b]; });

  vi nims(N);
  map<pii, int> memo;
  for (auto e : order) {
    pii key = {A[e], e % A[e]};
    if (memo.contains(key)) {
      nims[e] = memo[key];
      continue;
    }
    set<int> seen;
    for (int i = e % A[e]; i < N; i += A[e]) {
      if (A[i] > A[e]) {
        seen.insert(nims[i]);
      }
    }
    int mex = 0;
    while (seen.contains(mex)) {
      mex++;
    }
    nims[e] = mex;
    memo[key] = nims[e];
  }

  for (auto e : nims) {
    cout << (e == 0 ? 'B' : 'A');
  }
  cout << '\n';
}
