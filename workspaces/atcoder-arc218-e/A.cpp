#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ll long long
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

const int MOD = 998244353;

struct FT {
  vi s;
  FT(int n) : s(n) {}
  void update(int i, int dif) {  // a[i] += dif
    for (; i < sz(s); i |= i + 1) s[i] += dif;
  }
  int query(int i) {  // sum of values in [0, i)
    int r = 0;
    for (; i > 0; i &= i - 1) r += s[i - 1];
    return r;
  }
  int lower_bound(int sum) {  // min i st sum of [0, i] >= sum
    // Returns n if no sum is >= sum, or -1 if empty sum is.
    // (assumes a[i] >= 0)
    if (sum <= 0) return -1;
    int i = 0;
    for (int pw = 1 << 25; pw; pw >>= 1) {
      if (i + pw <= sz(s) && s[i + pw - 1] < sum) i += pw, sum -= s[i - 1];
    }
    return i;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // P2[i] = P[i+a-b mod N]
  //
  // N ways, pie 0+_, _+0
  // 0: N-1
  // 1: N-2
  // 2: N-2
  // ...
  // N-1: N-2
  //
  // 2x2 matrix exponentiation
  //
  // P[0] has P[0]-1 inversions
  // moving it to back makes it have N-P[0] inversions
  // delta is N-P[0]-(P[0]-1) = N-1-2P[0]
  //
  // sum for N-1 shifts:
  // base*(N-1) +
  // (N-1-2P[0])(N-1) +
  // (N-1-2P[1])(N-2) +
  // ...
  // (N-1-2P[N-2])(1)
  // =
  // base*(N-1) +
  // (N-1)*N*(N-1)/2 +
  // 2*(P[0]*(N-1) + P[1]*(N-2) + ... + P[N-2]*(1))
  //
  // for odd:
  // if first op is i
  // ... +
  // 2*(P[i]*(N-1) + P[i-1]*(N-2) + ... + P[i+2]*(1))
  //
  // convolution? a-b = i-(N-1) mod N
  // sure
  //
  // how to update?
  // swap x,x+1
  // a-b = i-(N-1) mod N
  //
  //
  // wait...
  // it's all just shifts... just reversed sometimes
  //
  // a means reverse, then P2[i] = P[i+a mod N]
  // 0: 0
  // 1: 1
  // 2: 1
  // ...
  // N-1: 1
  //
  // i think we can use the same matrix exponentiation
  //
  // so base for even:
  // 0: 1
  // 1: 0
  // 2: 0
  // ...
  // N-1: 0
  //
  // base for odd:
  // 0: 0
  // 1: 1
  // 2: 1
  // ...
  // N-1: 1
  // odd works on reverse array i believe?
  //
  // let's make these binary:
  // A:
  // N-1, N-2
  // (N-1)*(N-2), N-1+(N-2)*(N-2)
  //
  // even b:
  // 1, 0
  //
  // odd b:
  // 0, 1
  //
  // Y=b@A^e
  // Y[0,0] * base
  // Y[0,1] * shift sums
  //
  // updates are simple

  int N, Q;
  cin >> N >> Q;

  vi P(N);
  for (auto &e : P) cin >> e;

  auto inversions = [&](vi P) -> int {
    FT ft(N + 1);
    int rv = 0;
    for (auto e : P) {
      (rv += ft.query(N + 1) - ft.query(e + 1)) %= MOD;
      ft.update(e, 1);
    }
    return rv;
  };

  auto matmul = [&](vc<vi> A, vc<vi> B) -> vc<vi> {
    vc rv(sz(A), vi(sz(B[0]), 0));
    rep(i, 0, sz(A)) {
      rep(j, 0, sz(B[0])) {
        rep(k, 0, sz(A[0])) { (rv[i][j] += A[i][k] * B[k][j]) %= MOD; }
      }
    }
    return rv;
  };

  auto matpow = [&](vc<vi> A, int e) -> vc<vi> {
    vc rv(sz(A), vi(sz(A), 0));
    rep(i, 0, sz(A)) { rv[i][i] = 1; }
    for (; e; e >>= 1, A = matmul(A, A)) {
      if (e & 1) {
        rv = matmul(rv, A);
      }
    }
    return rv;
  };

  int even_base = inversions(P), even_shift_sum = 0;
  (even_shift_sum += even_base * (N - 1)) %= MOD;
  auto even_contrib = [&](int i) -> int {
    if (i == N - 1) return 0;
    return ((N - P[i]) - (P[i] - 1)) * (N - 1 - i) % MOD;
  };
  rep(i, 0, N) { (even_shift_sum += even_contrib(i)) %= MOD; }

  int odd_base = (N * (N - 1) / 2 - even_base) % MOD, odd_shift_sum = 0;
  (odd_shift_sum += odd_base * (N - 1)) %= MOD;
  auto odd_contrib = [&](int i) -> int {
    if (i == 0) return 0;
    return ((N - P[i]) - (P[i] - 1)) * i % MOD;
  };
  rep(i, 0, N) { (odd_shift_sum += odd_contrib(i)) %= MOD; }

  vc<vi> A = {{N - 1, N - 2},
              {(N - 1) * (N - 2) % MOD, (N - 1 + (N - 2) * (N - 2)) % MOD}};
  vc<vi> even_b = {{1, 0}}, odd_b = {{0, 1}};

  while (Q--) {
    int x, K;
    cin >> x >> K;
    x--;

    (even_shift_sum -= even_base * (N - 1)) %= MOD;
    (even_shift_sum -= even_contrib(x)) %= MOD;
    (even_shift_sum -= even_contrib(x + 1)) %= MOD;
    if (P[x] > P[x + 1]) {
      (even_base -= 1) %= MOD;
    }

    (odd_shift_sum -= odd_base * (N - 1)) %= MOD;
    (odd_shift_sum -= odd_contrib(x)) %= MOD;
    (odd_shift_sum -= odd_contrib(x + 1)) %= MOD;
    if (P[x] < P[x + 1]) {
      (odd_base -= 1) %= MOD;
    }

    swap(P[x], P[x + 1]);

    if (P[x] > P[x + 1]) {
      (even_base += 1) %= MOD;
    }
    (even_shift_sum += even_base * (N - 1)) %= MOD;
    (even_shift_sum += even_contrib(x)) %= MOD;
    (even_shift_sum += even_contrib(x + 1)) %= MOD;

    if (P[x] < P[x + 1]) {
      (odd_base += 1) %= MOD;
    }
    (odd_shift_sum += odd_base * (N - 1)) %= MOD;
    (odd_shift_sum += odd_contrib(x)) %= MOD;
    (odd_shift_sum += odd_contrib(x + 1)) %= MOD;

    int ans;
    if (K % 2 == 0) {
      auto y = matmul(even_b, matpow(A, K / 2));
      ans = (y[0][0] * even_base + y[0][1] * even_shift_sum) % MOD;
    } else {
      auto y = matmul(odd_b, matpow(A, (K - 1) / 2));
      ans = (y[0][0] * odd_base + y[0][1] * odd_shift_sum) % MOD;
    }
    (ans += MOD) %= MOD;
    cout << ans << '\n';
  }
}
