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

	//

	int T;
	cin >> T;

	while (T--) {
		int N, Q;
		cin >> N >> Q;

		vi P(N);
		for (auto &e : P) cin >> e;

		// vi lb(N);
		// while (Q--) {
		// 	int l, r;
		// 	cin >> l >> r;
		// 	l--;

		// 	lb[l] = P[l];
		// 	int lbprev = lb[l];
		// 	vc<pii> ranges;
		// 	ranges.eb(l, r);
		// 	rep(i, l + 1, r) {
		// 		lb[i] = min(lb[i - 1], P[i]);
		// 		if (lb[i] != lbprev) {
		// 			ranges.back().sd = i;
		// 			ranges.eb(i, r);
		// 		}
		// 		lbprev = lb[i];
		// 	}

		// 	int ans = 0;
		// 	rep(i, l, r) {
		// 		rep(j, l, i) {
		// 			if (lb[j] <= lb[i]) continue;
		// 			ans += 1;
		// 		}
		// 	}

		// 	for (auto [l2, r2] : ranges) {
		// 		int y = l2 - l, w = r2 - l2;
		// 		if (l2 == l) {
		// 			w -= 1;
		// 		}
		// 		if (w < y) continue;
		// 		int x = (w - y) / 2;
		// 		ans += x * (w - x - y);
		// 	}
		// 	cout << ans << '\n';
		// }

		vc<pii> queries(Q);
		for (auto &[l, r] : queries) {
			cin >> l >> r;
			l--;
		}

		vc<vi> by_l(N);
		rep(i, 0, Q) {
			auto [l, r] = queries[i];
			by_l[l].pb(i);
		}

		vi ans(Q);
		vc<pii> stack;
		vi ps;
		ps.pb(0);
		for (int i = N - 1; i >= 0; i--) {
			int r = i + 1;
			while (sz(stack) > 0 and P[i] < P[stack.back().fs]) {
				r = stack.back().sd;
				stack.pop_back();
				ps.pop_back();
			}
			stack.eb(i, r);
			ps.pb(ps.back() + i * (r - i));

			for (auto j : by_l[i]) {
				auto [l, r] = queries[j];

				int l2 = 0, r2 = sz(stack);
				while (l2 < r2) {
					int m = l2 + (r2 - l2) / 2;
					stack[m].sd <= r ? r2 = m : l2 = m + 1;
				}

				int sum = ps[sz(stack)] - ps[l2];
				if (l2 - 1 >= 0) {
					auto [l3, r3] = stack[l2 - 1];
					sum += l3 * (r - l3);
				}
				sum -= l * (r - l);

				int r3prev = -1;
				for (int k = 1; k < r - l; k *= 2) {
					if (l + k < r3prev) continue;

					int l2 = 0, r2 = sz(stack) - 1;
					while (l2 < r2) {
						int m = l2 + (r2 - l2) / 2;
						stack[m].fs <= l + k ? r2 = m : l2 = m + 1;
					}

					auto [l3, r3] = stack[l2];
					int y = l3 - l, w = min(r3, r) - l3;
					if (l3 == l) {
						w -= 1;
					}
					if (w >= y) {
						int x = (w - y) / 2;
						sum += x * (w - x - y);
					}

					r3prev = r3;
				}
				ans[j] = sum;
			}
		}
		for (auto e : ans) {
			cout << e << '\n';
		}
	}
}
