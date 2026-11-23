#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
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
typedef pair<double, double> pdd;
typedef vc<int> vi;
typedef vc<double> vd;

const double EPS = 1e-9;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

vc<vd> matmul(vc<vd> a, vc<vd> b) {
  vc rv(sz(a), vd(sz(b[0]), 0));
  rep(i, 0, sz(a)) rep(j, 0, sz(b[0])) rep(k, 0, sz(a[0])) {
    rv[i][j] += a[i][k] * b[k][j];
  }
  return rv;
}

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  while (N--) {
    vc<pdd> tri(3);
    for (auto &[x, y] : tri) {
      cin >> x >> y;
    }
    pdd d1, d2;
    cin >> d1.fs >> d1.sd >> d2.fs >> d2.sd;

    auto cross = [&](pdd a, pdd b) -> double {
      return a.fs * b.sd - a.sd * b.fs;
    };

    auto sub = [&](pdd a, pdd b) -> pdd { return {a.fs - b.fs, a.sd - b.sd}; };

    auto dot = [&](pdd a, pdd b) -> double {
      return a.fs * b.fs + a.sd * b.sd;
    };

    auto mag2 = [&](pdd a) -> double { return dot(a, a); };

    if (abs(cross(d1, d2)) < EPS) {
      bool perp = false;
      rep(i, 0, 3) {
        if (abs(dot(sub(tri[i], tri[(i + 1) % 3]), d1)) < EPS) {
          perp = true;
        }
      }
      if (perp) {
        cout << "1\n";
      } else {
        cout << "2\n";
      }
      continue;
    }

    auto solve = [&](vc<pdd> tri, pdd d1, pdd d2) -> int {
      vc<vd> A = {{d1.fs / mag2(d1), d1.sd / mag2(d1)},
                  {d2.fs / mag2(d2), d2.sd / mag2(d2)}};
      for (auto &[x, y] : tri) {
        auto v = matmul(A, {{x}, {y}});
        x = v[0][0], y = v[1][0];
      }

      sort(all(tri));
      if (abs(tri[0].fs - tri[1].fs) < EPS) {
        return 1;
      } else if (abs(tri[1].fs - tri[2].fs) < EPS) {
        return 1;
      }

      double ymin = min(tri[0].sd, tri[1].sd), ymax = max(tri[0].sd, tri[1].sd),
             y = tri[2].sd;
      if (abs(y - ymin) < EPS) {
        return 2;
      } else if (abs(y - ymax) < EPS) {
        return 2;
      } else if (y < ymin) {
        return 3;
      } else if (y < ymax) {
        return 3;
      } else {
        return 4;
      }
    };
    int ans = max(solve(tri, d1, d2), solve(tri, d2, d1));
    if (ans > 3) {
      cout << "forever\n";
    } else {
      cout << ans << '\n';
    }
  }
}
