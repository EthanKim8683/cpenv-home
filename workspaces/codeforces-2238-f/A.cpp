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

const int MAXK = 2e5;
const int LOGK = __lg(MAXK);
const int MOD = 1e9 + 7;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	// number of rehires = sum_{all fires} 2^{current day - day fired - 1}
	//
	// K = number of original hires + number of rehires
	//
	// each "split" of a node introduces one new internal and one new leaf node,
	// so number of fires = number of original hires kept + 1
	//
	// if we keep x original hires, we need to add x + 1 powers of two (0, 1, 2,
	// ..., 2^{N-1})
	//
	// the sum of the powers of two must be K - x
	//
	// or maybe we could have a less explicit formulation
	//
	// we could process origin hires and fires together using a DP that tracks
	// the number of undetermined nodes
	//
	// i think we aren't making enough use of the fact that we're working with
	// powers of two
	//
	// maybe i could try PIE?
	//
	// i misread statement: the number of firings should be minimal possible
	//
	// so the number of firings should never exceed ~\log_2(K = 2e5)
	//
	// this makes it a lot easier
	//
	// the minimum number of powers of two required to make a number is its
	// bitcount
	//
	// iterate through x and stop when the bitcount of K - x is no greater than
	// x + 1
	//
	// we can then try to make K - x using x + 1 powers of two
	//
	// this can be done relatively quickly with DP
	//
	// the number of firings can exceed ~\log_2(K = 2e5) because there can be
	// K - x much greater than the greatest power of two we can use (e.g. when N
	// is small)
	//
	// well, obviously if K - x is greater than the greatest power of two we can
	// use, we must use the greatest power of two possible for all bits
	// exceeding the greatest power of two we can use
	//
	// also, we don't add powers of two exactly, it's powers of two minus one
	// (0, 1, 3, ..., 2^N-1). rookie mistake...

	vi fact(2 * MAXK + 1);
	fact[0] = 1;
	rep(i, 1, 2 * MAXK + 1) { fact[i] = fact[i - 1] * i % MOD; }

	auto mod_pow = [&](int x, int y) -> int {
		int rv = 1;
		for (x %= MOD; y; y >>= 1, (x *= x) %= MOD) {
			if (y & 1) {
				(rv *= x) %= MOD;
			}
		}
		return rv;
	};

	auto mod_inv = [&](int x) -> int { return mod_pow(x, MOD - 2); };

	vi inv(MAXK + 2);
	rep(i, 1, MAXK + 2) { inv[i] = mod_inv(i); }

	vi inv_fact(MAXK + 1);
	inv_fact[0] = 1;
	rep(i, 1, MAXK + 1) { inv_fact[i] = inv_fact[i - 1] * inv[i] % MOD; }

	auto binom = [&](int n, int k) -> int {
		return fact[n] * inv_fact[n - k] % MOD * inv_fact[k] % MOD;
	};

	int T;
	cin >> T;

	vc<pii> testcases(T);
	vi ans(T);
	vc<vi> by_max_exp(LOGK + 1);
	rep(i, 0, T) {
		auto &[N, K] = testcases[i];
		cin >> N >> K;

		int max_exp = min(N - 1, LOGK);
		if (max_exp == 0) {
			ans[i] = binom(2 * K, K) * inv[K + 1] % MOD;
			continue;
		}

		by_max_exp[max_exp].pb(i);
	}

	vc dp(2, vc(MAXK + 1, vi(LOGK + 1, 0)));
	dp[0][0][0] = 1;
	rep(i, 0, LOGK + 1) {
		int hires = (1 << i) - 1;
		if (i + 1 <= LOGK) {
			rep(j, 0, MAXK + 1) {
				rep(k, 0, LOGK + 1) {
					for (int l = 0; j + l * hires <= MAXK and k + l <= LOGK;
						 l++) {
						(dp[(i + 1) % 2][j + l * hires][k + l] +=
						 dp[i % 2][j][k] * inv_fact[l]) %= MOD;
					}
				}
			}
		}

		for (auto j : by_max_exp[i]) {
			auto [N, K] = testcases[j];

			int mask = (1 << (i + 1)) - 1;
			int le = __builtin_popcount((K + 1) & mask),
				gt = ((K + 1) & ~mask) >> i;
			int x = le + gt - 1;

			ans[j] = 0;
			int total_hires = K - x - gt * hires, total_fires = x + 1 - gt;
			rep(k, 0, min(total_hires / hires, total_fires) + 1) {
				(ans[j] += dp[i % 2][total_hires - k * hires][total_fires - k] *
						   inv_fact[k + gt]) %= MOD;
			}
			(ans[j] *= fact[x + 1]) %= MOD;
			(ans[j] *= binom(2 * x, x)) %= MOD;
			(ans[j] *= inv[x + 1]) %= MOD;
		}

		rep(j, 0, MAXK + 1) {
			rep(k, 0, LOGK + 1) { dp[i % 2][j][k] = 0; }
		}
	}

	for (auto e : ans) {
		cout << e << '\n';
	}
}
