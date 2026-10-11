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

struct RURQ {
  using T = int;
  using S = int;
  T e = INF;
  S id = 0;
  T op(T u, T v) { return min(u, v); }
  T use(T u, S v) { return u + v; }
  S lazyop(S u, S v) { return u + v; }

  int logn, n;
  vc<T> segs;
  vc<S> lazy;
  RURQ(int nb)
      : logn(__lg(2 * nb - 1)), n(1 << logn), segs(2 * n, e), lazy(2 * n, id) {
    for (int i = n - 1; i > 0; i--) {
      segs[i] = op(segs[i << 1], segs[i << 1 | 1]);
    }
  }
  void apply(int i, S v) {
    segs[i] = use(segs[i], v);
    if (i < n) lazy[i] = lazyop(lazy[i], v);
  }
  void down(int i) {
    if (lazy[i] == id) return;
    apply(i << 1, lazy[i]);
    apply(i << 1 | 1, lazy[i]);
    lazy[i] = id;
  }
  void push(int i) {
    for (int j = logn; j > 0; j--) down((i + n) >> j);
  }
  void pull(int i) {
    for (i += n; i >>= 1;)
      segs[i] = use(op(segs[i << 1], segs[i << 1 | 1]), lazy[i]);
  }
  void update(int l, int r, S v) {
    if (l >= r) return;
    int l0 = l, r0 = r;
    push(l0), push(r0 - 1);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) apply(l++, v);
      if (r & 1) apply(--r, v);
    }
    pull(l0), pull(r0 - 1);
  }
  T query(int l, int r) {
    if (l >= r) return e;
    T lv = e, rv = e;
    push(l), push(r - 1);
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lv = op(lv, segs[l++]);
      if (r & 1) rv = op(segs[--r], rv);
    }
    return op(lv, rv);
  }
  void assign(int i, T v) {
    push(i);
    segs[i + n] = v;
    pull(i);
  }
  int get(int i) { return segs[i + n]; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int Q;
  cin >> Q;

  vi X(Q);
  for (auto &e : X) cin >> e;

  vi cc;
  cc.pb(0);
  for (auto e : X) {
    cc.pb(abs(e));
  }
  sort(all(cc));
  reverse(all(cc));
  cc.erase(unique(all(cc)), cc.end());

  auto compress = [&](int x) -> int {
    return lower_bound(all(cc), x, greater<int>()) - cc.begin();
  };

  RURQ st(sz(cc));
  map<int, int> counts;
  st.assign(compress(0), 0);
  rep(i, 0, Q) {
    int x = abs(X[i]), j = compress(x);
    if (X[i] > 0) {
      if (counts[x] == 0) {
        st.update(j, j + 1, x - INF);
      }
      counts[x] += 1;
      st.update(j + 1, sz(cc), 1);
    } else {
      counts[x] -= 1;
      st.update(j + 1, sz(cc), -1);
      if (counts[x] == 0) {
        st.update(j, j + 1, INF - x);
      }
    }
    cout << st.query(0, sz(cc)) << ' ';
    // rep(i, 0, sz(cc)) { cerr << st.get(i) << ' '; }
    // cerr << '\n';
  }
  cout << '\n';
}
