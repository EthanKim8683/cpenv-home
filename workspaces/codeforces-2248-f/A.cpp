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

const int INF = 1e18;

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
	cin >> T;

	while (T--) {
		int N, M, K;
		cin >> N >> M >> K;

		vc V(N, vi(M));
		for (auto &r : V) {
			for (auto &e : r) {
				cin >> e;
			}
		}

		if (N == 1 and M == 1) {
			if (V[0][0] < 0) {
				cout << "-1\n";
				continue;
			}
			
			cout << "0\n";
			continue;
		}
		
		if (M == 1) {
			auto transpose = [&](vc<vi> A) -> vc<vi> {
				vc AT(sz(A[0]), vi(sz(A)));
				rep(i, 0, sz(A)) {
					rep(j, 0, sz(A[0])) {
						AT[j][i] = A[i][j];
					}
				}
				return AT;
			};
			V = transpose(V);
			swap(N, M);
		}	
		
		if (N == 1) {
			if (M == 2) {
				if (K == 1) {
					cout << "0\n";
					continue;
				}

				cout << max(V[0][0], V[0][1]) - min(V[0][0], V[0][1]) << '\n';
				continue;
			}

			cout << "skip\n";
			continue;
		}
		
		/*
		lhs - rhs
		= (V[i][j]-x) - (row_sums[i]-V[i][j] - x*(M-1)) - (col_sums[j]-V[i][j] - x*(N-1))
		= 3*V[i][j] - row_sums[i] - col_sums[j] + (M+N-3)*x
		
		3*V[i][j] - row_sums[i] - col_sums[j] + (M+N-3)*x >= 0
		(M+N-3)*x >= row_sums[i] + col_sums[j] - 3*V[i][j]
		x >= (row_sums[i] + col_sums[j] - 3*V[i][j]) / (M+N-3)
		*/	
			
		vi row_sums(N, 0), col_sums(M, 0);
		rep(i, 0, N) {
			rep(j, 0, M) {
				row_sums[i] += V[i][j];
				col_sums[j] += V[i][j];
			}
		}
		
		auto ceil_div = [&](int x, int y) -> int {
			if (y == 0) return INF;
			return (x - 1) / y + 1;
		};

		vi costs;
		rep(i, 0, N) {
			rep(j, 0, M) {
				int d = row_sums[i] + col_sums[j] - 3*V[i][j];
				costs.pb(d <= 0 ? 0 : ceil_div(d, M+N-3));
			}
		}
		sort(all(costs));
		cout << costs[K-1] << '\n';
	}
}
