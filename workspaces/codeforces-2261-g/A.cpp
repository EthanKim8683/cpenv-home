#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

// #define int long long
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

const int LOGA = 25;

struct trie {
  struct node {
    int ch[2]{};
    long long count = 0;
  };
  vc<node> d;
  trie() : d(1) {}
  int ensure(int &a) { return a ?: (a = sz(d), d.eb(), sz(d) - 1); }
  void add(int ps, int and_sum, int delta) {
    int a = 0;
    for (int i = 25 - 1; i >= 0; i--) {
      a = ensure(d[a].ch[(ps ^ and_sum) >> i & 1]);
      d[a].count += delta * (and_sum & 1ll << i);
    }
  }
  long long get(int ps) {
    int a = 0;
    long long rv = 0;
    for (int i = 25 - 1; i >= 0; i--) {
      a = d[a].ch[ps >> i & 1];
      if (!a) return 0;
      rv += d[a].count;
    }
    return rv;
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // if len is even, f is 0
  //
  // if len is odd, f depends on which bits are set in all elements
  //
  // going top to bottom, ending when a bit is set in the sum but only some of
  // the elements, contribute each bit

  int T;
  cin >> T;

  while (T--) {
    int N;
    cin >> N;

    vi A(N);
    for (auto &e : A) cin >> e;

    // int ans = 0;
    // rep(l, 0, N) {
    //   for (int r = l + 1; r <= N; r += 2) {
    //     int and_sum = (1ll << LOGA) - 1, or_sum = 0, xor_sum = 0;
    //     rep(i, l, r) {
    //       and_sum &= A[i];
    //       or_sum |= A[i];
    //       xor_sum ^= A[i];
    //     }
    //     for (int i = LOGA - 1; i >= 0; i--) {
    //       if (~xor_sum >> i & 1) continue;
    //       if ((and_sum ^ or_sum) >> i & 1) break;
    //       ans += 1ll << i;
    //     }
    //   }
    // }
    // cout << ans << '\n';

    vi ps(N + 1);
    ps[0] = 0;
    rep(i, 0, N) { ps[i + 1] = ps[i] ^ A[i]; }

    trie t;
    vi and_sums(N, (1ll << LOGA) - 1);
    long long ans = 0;
    rep(i, 0, N) {
      for (int j = i - 1; j >= 0; j--) {
        if ((and_sums[j] & A[i]) == and_sums[j]) break;
        t.add(ps[j], and_sums[j], -1);
        and_sums[j] &= A[i];
        t.add(ps[j], and_sums[j], 1);
      }
      and_sums[i] &= A[i];
      t.add(ps[i], and_sums[i], 1);
      ans += t.get(ps[i + 1]);
    }
    cout << ans << '\n';
  }
}
