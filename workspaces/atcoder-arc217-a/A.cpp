#include <algorithm>
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

int gray_code(int x) { return x ^ x >> 1; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  vi P(9);
  iota(all(P), 1);
  int best = 100;
  vc<vi> bests;
  do {
    int ps = 0, sum = 0;
    for (auto e : P) {
      ps ^= e;
      sum += ps;
    }
    if (sum < best) {
      best = sum;
      bests.clear();
    }
    if (sum == best) {
      bests.pb(P);
    }
  } while (next_permutation(all(P)));
  cerr << best << '\n';
  for (auto P : bests) {
    for (auto e : P) {
      cerr << e << ' ';
    }
    cerr << '\n';
    cerr << '\t';
    int ps = 0;
    for (auto e : P) {
      ps ^= e;
      cerr << ps << ' ';
    }
    cerr << '\n';
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    if (N % 2 == 1) {
      rep(i, 1, 2 * N) {
        int x = gray_code(i);
        if (x <= N) {
          cout << gray_code(i) << ' ';
        }
      }
    } else {
      rep(i, 1, 2 * N) {
        int x = gray_code(i);
        if (x < N) {
          cout << gray_code(i) << ' ';
        }
      }
      cout << N;
    }
    cout << '\n';
  }
}
