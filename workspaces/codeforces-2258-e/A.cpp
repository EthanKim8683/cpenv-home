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

const int MAXN = 2e5;
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

  vc<bool> is_prime(2 * MAXN + 1, true);
  is_prime[0] = false;
  is_prime[1] = false;
  for (int i = 2; i * i <= 2 * MAXN; i++) {
    if (!is_prime[i]) continue;
    for (int j = i * i; j <= 2 * MAXN; j += i) {
      is_prime[j] = false;
    }
  }

  vc<bool> is_prime_power(2 * MAXN + 1, false);
  is_prime_power[1] = true;
  rep(i, 2, 2 * MAXN + 1) {
    if (!is_prime[i]) continue;
    for (int j = i; j <= 2 * MAXN; j *= i) {
      is_prime_power[j] = true;
    }
  }

  vc<vi> divisors(MAXN + 1);
  rep(i, 1, MAXN + 1) {
    if (!is_prime_power[i]) continue;
    for (int j = i; j <= MAXN; j += i) {
      divisors[j].pb(i);
    }
  }

  vi next_prime_power(2 * MAXN + 1, INF);
  for (int i = 2 * MAXN; i >= 0; i--) {
    if (i + 1 <= 2 * MAXN) {
      next_prime_power[i] = next_prime_power[i + 1];
    }
    if (is_prime_power[i]) {
      next_prime_power[i] = i;
    }
  }

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    int n = next_prime_power[N + 1];

    vc<vi> indices(n + 1);
    rep(i, 0, N) {
      for (auto e : divisors[A[i]]) {
        indices[e].pb(i);
      }
    }

    using S = int;
    auto op = [&](S a, S b) -> S { return max(a, b); };
    auto e = [&]() -> S { return -INF; };
    segtree<S, op, e> st(N);
    vi ans;
    rep(i, 1, n + 1) {
      if (!is_prime_power[i]) continue;
      vc<pii> ranges;
      int l = 0;
      for (auto e : indices[i]) {
        ranges.eb(l, e);
        l = e + 1;
      }
      ranges.eb(l, N);
      bool found = false;
      for (auto [l, r] : ranges) {
        if (l == r) continue;
        if (st.prod(0, l + 1) >= r) continue;
        found = true;
        st.set(l, r);
      }
      if (found) {
        ans.pb(i);
      }
    }
    cout << sz(ans) << '\n';
    for (auto e : ans) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
