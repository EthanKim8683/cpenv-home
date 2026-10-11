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

  // find one, then find its xor with rest
  //
  // if we know every p's xor with b0, we know all the p's relationships
  //
  // all relative xors will be different
  //
  // we can construct all candidate permutations just from these relationships
  //
  // now, we find their inverse
  //
  // p0 ^ pi = (p0 ^ b0) ^ (pi ^ b0)

  int N;
  cin >> N;

  auto query = [&](int i, int j) -> int {
    cout << "? " << i << ' ' << j << endl;
    int rv;
    cin >> rv;
    if (rv == -1) {
      exit(0);
    }
    return rv;
  };

  auto answer = [&](int n, vi p) -> void {
    cout << "!\n";
    cout << n << '\n';
    for (auto e : p) {
      cout << e << ' ';
    }
    cout << endl;
  };

  vi xorp(N), xorb(N);
  rep(i, 0, N) { xorp[i] = query(i, 0); }
  rep(i, 0, N) { xorb[i] = query(0, i); }

  int n = 0;
  vi p;
  rep(i, 0, N) {
    vi P(N);
    P[0] = i;
    rep(j, 1, N) { P[j] = P[0] ^ xorp[0] ^ xorp[j]; }

    if (*max_element(all(P)) > N - 1) continue;

    vi B(N);
    rep(j, 0, N) { B[P[j]] = j; }

    bool ok = true;
    rep(j, 0, N) { ok = ok and (P[j] ^ B[0]) == xorp[j]; }
    rep(j, 0, N) { ok = ok and (P[0] ^ B[j]) == xorb[j]; }
    rep(j, 0, N) { ok = ok and (B[0] ^ B[j]) == (xorb[0] ^ xorb[j]); }
    if (!ok) continue;

    n += 1;
    p = P;
  }
  answer(n, p);
}
