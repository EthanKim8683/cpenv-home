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

  //

  int N, Q;
  cin >> N >> Q;

  string S;
  cin >> S;

  vc by_mask(4, FT(N - 1));
  rep(i, 0, N - 1) {
    int mask = (S[i] - '0') << 1 | (S[i + 1] - '0');
    by_mask[mask].update(i, 1);
  }

  while (Q--) {
    int l, r;
    cin >> l >> r;
    l--;

    vi c(4, 0);
    rep(i, 0, 4) { c[i] += by_mask[i].query(r - 1) - by_mask[i].query(l); }
    int mask = (S[r - 1] - '0') << 1 | (S[l] - '0');
    c[mask] += 1;

    // for (auto e : c) {
    //   cerr << e << ' ';
    // }
    // cerr << '\n';

    auto c2 = c;
    if (c2[0b01] != c2[0b10]) {
      c2[0b01] = c2[0b10] = max(c2[0b01], c2[0b10]) + abs(c2[0b01] - c2[0b10]);
    }

    if (c2[0b00] > c2[0b11]) {
      swap(c2[0b00], c2[0b11]);
    }

    int x;
    if (c2[0b00] > c2[0b01] and c2[0b11] > c2[0b10]) {
      int d = min(c2[0b11] - c2[0b00], c2[0b00] - c2[0b01]);
      c2[0b11] -= d;
      c2[0b01] += d;
      c2[0b10] += d;
      if (c2[0b00] == c2[0b11]) {
        // cerr << "a\n";
        int d = (c2[0b00] - c2[0b01]) / 3;
        c2[0b00] -= d;
        c2[0b01] += 2 * d;
        c2[0b10] += 2 * d;
        c2[0b11] -= d;
        x = c2[0b11];
      } else {
        // cerr << "b\n";
        int d = (c2[0b11] - c2[0b01]) / 2;
        c2[0b01] += d;
        c2[0b10] += d;
        c2[0b11] -= d;
        x = c2[0b11];
      }
    } else if (c2[0b11] > c2[0b10]) {
      // cerr << "c\n";
      int d = (c2[0b11] - c2[0b10]) / 2;
      c2[0b01] += d;
      c2[0b10] += d;
      c2[0b11] -= d;
      x = c2[0b11];
    } else {
      // cerr << "d\n";
      x = c2[0b01];
    }
    int ans = 4 * x;
    for (auto e : c) {
      ans -= e;
    }
    cout << ans << '\n';
  }
}
