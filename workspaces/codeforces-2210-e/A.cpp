#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
#include <bits/stdc++.h>

using namespace std;

#define int long long
#define double long double
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

template <class S, auto op, auto inv>
struct dsu_with_potentials {
	static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
				  "op must work as S(S, S)");
	static_assert(std::is_convertible_v<decltype(inv), std::function<S(S)>>,
				  "inv must work as S(S)");

   private:
	std::vector<int> root;
	std::vector<S> V;

   public:
	dsu_with_potentials() {}
	dsu_with_potentials(int n, S nil) : root(n, -1), V(n, nil) {}

	int leader(int a) {
		if (root[a] < 0) return a;
		int p = leader(root[a]);
		V[a] = op(V[a], V[root[a]]);
		return root[a] = p;
	}

	bool merge(int a, int b, S v) {
		int a2 = leader(a), b2 = leader(b);
		if (a2 == b2) return op(V[b], inv(V[a])) == v;
		if (root[a2] > root[b2]) {
			std::swap(a2, b2);
			std::swap(a, b);
			v = inv(v);
		}
		root[a2] += root[b2];
		root[b2] = a2;
		V[b2] = op(op(v, V[a]), inv(V[b]));
		return true;
	}

	bool same(int a, int b) { return leader(a) == leader(b); }

	int size(int a) { return -root[leader(a)]; }

	S potential(int a) {
		leader(a);
		return V[a];
	}

	S voltage(int a, int b) { return op(potential(b), inv(potential(a))); }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main(signed argc, char **argv) {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

	// if we move a 0 from front to back, x increases by the number of 1s
	//
	// if we move a 1 from front to back, x decreases by the number of 0s
	//
	// we don't need to worry about an initial x because f(l, r) is the number
	// of unique numbers in a
	//
	// if there are z zeros and o ones and we decrease x by z, modulo m, we're
	// increasing by m - z = o, the number of 1s
	//
	// we only ever increase by the number of 1s, and we do this m times, so
	// f(l, r) = m / gcd(o, m)
	//
	// define g(l, r) = m / f(l, r) = gcd(o, m)
	//
	// the "at most 2 guesses" allowance is because o and z are interchangeable
	//
	// if we use a sliding window approach, if we replace a 0 with a 1 or vice
	// versa, g(., .), if not initially 1, will become 1 because o and o' would
	// be coprime
	//
	// if we have a sliding window of even size, g(., .) would go between 1 and
	// 2k every time the popped and pushed characters differ
	//
	// if we use this sliding window approach, we'll end up with periodic edges,
	// and so we want a coprime sized sliding window to get everything connected
	// (technically, though, we could get by with a set of sliding windows with
	// a gcd sum of 1)
	//
	// actually, doing a sliding window of 2k then 2(k + 1) reduces the number
	// of components to 2, at which point we could do an operation with m = 2 to
	// figure out how the two components relate

	mt19937 rng;
	if (argc > 1) {
		rng = mt19937(atoi(argv[1]));
	}

	int T;
	if (argc > 1) {
		T = 1;
	} else {
		cin >> T;
	}

	while (T--) {
		int N;
		if (argc > 1) {
			N = 1 + rng() % 20;
		} else {
			cin >> N;
		}

		string $S;
		if (argc > 1) {
			rep(i, 0, N) { $S += (char) ('0' + rng() % 2); }
			cerr << $S << '\n';
		}

		double $cost, $max_cost;
		if (argc > 1) {
			$cost = 0;
			$max_cost = max(30ll, 3 * N);
		}
		auto ask = [&](int l, int r) -> int {
			if (argc > 1) {
				$cost += (double) N / (r - l);
				if ($cost > $max_cost) {
					cerr << "cost " << $cost << " > " << $max_cost << '\n';
					exit(1);
				}

				int m = r - l, o = 0;
				rep(i, l, r) {
					if ($S[i] != '1') continue;
					o++;
				}
				return m / gcd(o, m);
			} else {
				cout << "? " << l + 1 << ' ' << r << endl;
				int rv;
				cin >> rv;
				if (rv == -1) exit(0);
				return rv;
			}
		};

		int $guesses = 0;
		auto answer = [&](string s) -> int {
			if (argc > 1) {
				$guesses++;
				if ($guesses > 2) {
					cout << "guesses " << $guesses << " > 2\n";
				}

				if (s != $S) {
					cout << "wa" << ' ' << s << '\n';
					return 0;
				} else {
					cout << "ok\n";
					return 1;
				}
			} else {
				cout << "! " << s << endl;
				int rv;
				cin >> rv;
				if (rv == -1) exit(0);
				return rv;
			}
		};

		dsu_with_potentials<int, [&](int a, int b) -> int { return a ^ b; },
							[&](int a) -> int { return a; }>
			d(N, 0);
		if (N <= 7) {
			rep(i, 0, N - 1) { d.merge(i, i + 1, ask(i, i + 2) == 2 ? 1 : 0); }
		} else {
			int k1 = N / 2;
			if (k1 % 2 != 0) {
				k1--;
			}
			int k2 = k1 + 2;

			int fprev = ask(0, k1);
			rep(i, 1, N - k1 + 1) {
				int a = i - 1, b = i + k1 - 1;
				if (d.same(a, b)) continue;
				int f = ask(i, i + k1);
				d.merge(a, b, f == fprev ? 0 : 1);
				fprev = f;
			}
			fprev = ask(0, k2);
			rep(i, 1, N - k2 + 1) {
				int a = i - 1, b = i + k2 - 1;
				if (d.same(a, b)) continue;
				int f = ask(i, i + k2);
				d.merge(a, b, f == fprev ? 0 : 1);
				fprev = f;
			}
			d.merge(0, 1, ask(0, 2) == 2 ? 1 : 0);
		}

		string ans;
		rep(i, 0, N) { ans += (char) ('0' + d.potential(i)); }
		if (answer(ans) == 1) continue;
		for (auto &e : ans) {
			e ^= 1;
		}
		if (answer(ans) == 1) continue;

		exit(1);
	}
}
