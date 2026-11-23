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
typedef pair<double, double> pdd;
typedef vc<int> vi;

const int MAXN = 220;
const int INF = 1e18;

struct dsu {
  vi d;
  dsu(int n) : d(n, -1) {}
  int leader(int a) { return d[a] < 0 ? a : d[a] = leader(d[a]); }
  bool merge(int a, int b) {
    a = leader(a), b = leader(b);
    if (a == b) return 0;
    if (d[a] > d[b]) swap(a, b);
    d[a] += d[b], d[b] = a;
    return 1;
  }
  int size(int a) { return -d[a]; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  mt19937 rng(time(nullptr));

#ifdef U
  int N = MAXN;

  vi H(N);
  iota(all(H), 0);
  shuffle(all(H), rng);

  // cerr << "H: ";
  // for (auto e : H) {
  //   cerr << e << ' ';
  // }
  // cerr << '\n';

  int count = 0;
  bool found = false;
  auto query = [&](vi Q) -> int {
    // cerr << "Q: ";
    // for (auto e : Q) {
    //   cerr << e << ' ';
    // }
    // cerr << '\n';

    count++;
    // assert(count <= 1510);

    if (Q == H) {
      found = true;
      return 0;
    }

    // cerr << "P: ";
    // for (auto e : Q) {
    //   cerr << H[e] << ' ';
    // }
    // cerr << '\n';

    vc<bool> seen(N, false);
    int rv = 0;
    rep(i, 0, N) {
      if (seen[i]) continue;
      for (int a = i; !seen[a]; a = H[Q[a]]) {
        seen[a] = true;
      }
      rv++;
    }

    // cerr << "rv: " << rv << '\n';
    return rv;
  };
#else
  int N;
  cin >> N;

  auto query = [&](vi Q) -> int {
    for (auto e : Q) {
      cout << e + 1 << ' ';
    }
    cout << endl;
    int rv;
    cin >> rv;
    return rv;
  };
#endif

  vi Q(N);
  iota(all(Q), 0);
  auto dfs = [&](auto self, vi S) -> void {
    if (sz(S) <= 1) return;
    if (sz(S) == 2) {
      swap(Q[S[0]], Q[S[1]]);
      return;
    }

    vi T(sz(S));
    rep(i, 0, sz(S)) { T[i] = Q[S[i]]; }
    shuffle(all(T), rng);
    rep(i, 0, sz(S)) { Q[S[i]] = T[i]; }

    int base = query(Q), n = 0;
    dsu d(sz(S));
    rep(i, 0, sz(S)) {
      bool found = false;
      pii best = {INF, -1};
      rep(j, 0, i) {
        if (d.leader(j) != j) continue;
        swap(Q[S[j]], Q[S[i]]);
        int test = query(Q);
        swap(Q[S[j]], Q[S[i]]);
        if (test > base) {
          d.merge(j, i);
          found = true;
          break;
        }
        chmin(best, pii{d.size(j), j});
      }
      if (!found and n >= 2) {
        int j = best.sd;
        swap(Q[S[j]], Q[S[i]]);
        base -= 1;
        d.merge(j, i);
      }
    }
    vc<vi> groups(sz(S));
    rep(i, 0, sz(S)) { groups[d.leader(i)].pb(S[i]); }
    for (auto e : groups) {
      self(self, e);
    }
  };
  vi S(N);
  iota(all(S), 0);
  dfs(dfs, S);

  vi Qinv(N);
  rep(i, 0, N) { Qinv[Q[i]] = i; }
  query(Qinv);

#ifdef U
  cerr << count << '\n';
  assert(found);
#endif
}
