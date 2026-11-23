#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
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

struct Line {
  mutable double k, m, p;
  bool operator<(const Line &o) const { return k < o.k; }
  bool operator<(double x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
  static constexpr double inf = numeric_limits<double>::max();
  double div(double a, double b) { return a / b; }
  bool isect(iterator x, iterator y) {
    if (y == end()) return x->p = inf, 0;
    if (x->k == y->k)
      x->p = x->m > y->m ? inf : -inf;
    else
      x->p = div(y->m - x->m, x->k - y->k);
    return x->p >= y->p;
  }
  void add(double k, double m) {
    auto z = insert({k, m, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  double query(double x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.k * x + l.m;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int N;
  cin >> N;

  vc<double> P(N);
  for (auto &e : P) cin >> e;

  LineContainer lc;
  double ans = 0;
  for (int i = N - 1; i >= 0; i--) {
    double x = P[i] * (i + 1);
    if (!lc.empty()) {
      chmax(x, P[i] * lc.query(i + 1));
    }
    chmax(ans, x);
    lc.add(1 - P[i], x);
  }
  cout << setprecision(10) << fixed << ans << '\n';
}
