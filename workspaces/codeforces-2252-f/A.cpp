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

vc<vi> virtual_tree(vi V, auto idx, auto lca) { sort(all(V)) }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  // if k_c = 1, then optimal solution is always if the component was in a
  // centroid
  //
  // can we greedily expand in the direction of the costliest subtree? yes
  //
  // technically i could solve this as an evil ds problem, but can i do better?
  // i could create virtual trees and then do centroid on that and it would be
  // like O(N\log(N)) total. and expanding in the direction of costliest subtree
  // is just an additional O(N\log(N)) i believe. honestly i think this is the
  // way. it's just modified virtual tree.
}
