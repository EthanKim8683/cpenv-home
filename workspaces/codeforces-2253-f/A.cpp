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

  // initial 4-beauty is always 4
  //
  // x, 2x, 3x, 4x, -> the only case when 4-beauty is 4
  //
  // gcd(x, 3x/2, 2x), x, 3x/2, 2x
  // x/2, x, 3x/2, 2x
  // x, 2x, 3x, 4x
  //
  // i guess we could just rearrange choices every time we append an element?
  //
  // if we append 4x, we now need x, 2x, 3x or 4x removed to satisfy x
  // depending on what we choose, another y could replace its own choice with
  // x's choice for free. if that y shares its original choice with another z,
  // then that z gets to pick again, repeating the cycle.
  //
  // or, to simplify, let's just naively assign x to 4x initially, then have a
  // "rethink" operation to allow x to reassign. rethink will take x and x_c and
  // return the total cost if x's choice became x_c and other numbers' choices
  // were adjusted optimally. rethink will work recursively, so basically if x_c
  // is equal to y, 2y, 3y or 4y, we want to rethink all y and y_c = x_c and a.

  int N;
  cin >> N;

  vi M(N);
  for (auto &e : M) cin >> e;
}
