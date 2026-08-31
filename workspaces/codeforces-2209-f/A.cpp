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

	// after the first operation, all value is contained in the leaves, so the
	// remaining k - 1 operations are on the leaves in order from greatest to
	// least
	//
	// the maximum distance property is interesting because each node only ever
	// has to consider two other nodes, the second of which is only considered
	// when the first is not available
	//
	// i imagine we can do something like re-rooting but with treap or something
}
