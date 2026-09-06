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

struct SuffixArray {
  vi sa, lcp;
  SuffixArray(string &s, int lim = 256) {  // or basic_string<int>
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)), y(n), ws(max(n, lim));
    x.pb(0), sa = lcp = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1ll, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i, 0, n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i, 0, n) ws[x[i]]++;
      rep(i, 1, lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i, 1, n) a = sa[i - 1], b = sa[i],
                   x[b] = (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    for (int i = 0, j; i < n - 1; lcp[x[i++]] = k)
      for (k &&k--, j = sa[x[i] - 1]; s[i + k] == s[j + k]; k++);
  }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // if we use suffix array, we can choose an element to correspond to the Kth
  // part and choose N - K elements after it, at least L apart, to be the parts
  // no less than it
  //
  // if we sort all the elements after the initially chosen element, we can
  // greedily choose the N - K elements... though, this doesn't guarantee the
  // other K - 1 elements will be choosable
  //
  // actually, i misread statement. let's sort the elements before the initially
  // chosen element, then greedily choose K - 1 elements
  //
  // now, the concern is over length
  //
  // actually, we don't even need to pick a singular element. we can represent a
  // string as a range on the suffix array
  //
  // actually, let's step back a bit. if we choose a substring to be the Kth
  // part, if the remaining substrings can be split into K - 1 parts, then our
  // answer is no less than the chosen substring
  //
  // i guess we can use suffix array and just binary search for the maximum
  // length starting at each suffix
  //
  // actually, i was wrong because if we have more parts than expected, a
  // smaller part might slip before the intended Kth part, resulting in an
  // invalid answer. i believe this is still salvageable though, since, if K >=
  // 3, we can always get exactly K parts

  int T;
  cin >> T;

  while (T--) {
    int N, L, K;
    cin >> N >> L >> K;

    string S;
    cin >> S;

    if (L * K > N) {
      cout << "NO\n";
      continue;
    }

    SuffixArray sa(S);
    pii ans;
    if (K == 1) {
      ans = {0, N};
    } else {
      int lcp = 0;
      rep(i, 0, sz(sa.sa)) {
        chmin(lcp, sa.lcp[i]);

        int l = sa.sa[i];
        if (!(l == 0 or (L <= l and l + L <= N))) continue;

        int n = N - max(K - l / L - 1, 0ll) * L - l;
        if (n < L) continue;

        bool ch = false;
        if (i == 0) {
          ch = true;
        } else {
          if (n > lcp and ans.sd > lcp) {
            ch = S[l + lcp] > S[ans.fs + lcp];
          } else {
            ch = n > ans.sd;
          }
        }
        if (ch) {
          ans = {l, n};
          lcp = N - l;
        }
      }
    }
    cout << "YES\n";
    cout << S.substr(ans.fs, ans.sd) << '\n';
  }
}
