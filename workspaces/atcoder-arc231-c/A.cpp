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

template <class S, auto op, auto e>
struct segtree {
  int n;
  vc<S> s;
  segtree(const vc<S> &v) : n(sz(v)), s(2 * n) {
    rep(i, 0, n) s[n + i] = v[i];
    for (int i = n - 1; i > 0; i--) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  segtree(int m) : segtree(vc(m, e())) {}
  S get(int i) { return s[n + i]; }
  void set(int i, S t) {
    for (s[i += n] = t; i >>= 1;) s[i] = op(s[i << 1], s[i << 1 | 1]);
  }
  S prod(int l, int r) {
    S lv = e(), rv = e();
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, s[l++]);
      if (r & 1) rv = op(s[--r], rv);
    }
    return op(lv, rv);
  }
};

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

    vi A(N);
    for (auto &e : A) cin >> e;

    vi B(N);
    for (auto &e : B) cin >> e;

    using S = array<int, 2>;
    auto op = [&](S a, S b) -> S {
      S rv;
      rep(i, 0, 2) {
        if (a[i] == -1) {
          rv[i] = -1;
        } else {
          rv[i] = b[a[i]];
        }
      }
      return rv;
    };
    auto e = [&]() -> S { return {0, 1}; };
    auto f = [&](int i) -> S {
      S rv;
      rep(j, 0, 2) {
        int p = (int[]) {A[i] - B[i], A[i] + B[i]}[j];
        if (A[i + 1] - B[i + 1] == p) {
          rv[j] = 0;
        } else if (A[i + 1] + B[i + 1] == p) {
          rv[j] = 1;
        } else if (abs(A[i + 1] - p) < B[i + 1]) {
          rv[j] = -1;
        } else if (A[i] + B[i] <= A[i + 1] - B[i + 1]) {
          rv[j] = 0;
        } else if (A[i] + B[i] <= A[i + 1] + B[i + 1]) {
          rv[j] = 1;
        } else {
          rv[j] = -1;
        }
      }
      return rv;
    };
    vc<S> v(N - 1);
    rep(i, 0, N - 1) { v[i] = f(i); }
    segtree<S, op, e> st(v);

    int Q;
    cin >> Q;

    while (Q--) {
      int p, s;
      cin >> p >> s;
      p--;

      B[p] = s;
      if (p - 1 >= 0) {
        st.set(p - 1, f(p - 1));
      }
      if (p + 1 < N) {
        st.set(p, f(p));
      }
      cout << (st.prod(0, N - 1)[0] == -1 ? "No" : "Yes") << '\n';
    }
  }
}
