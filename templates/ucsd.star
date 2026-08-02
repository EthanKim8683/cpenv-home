files = {
    "A.cpp": """#ifndef U
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
}""",
    "Makefile": """%.o: %.cpp
	g++ -g -O0 -DU=U -std=c++23 -fsanitize=undefined -Wall -Wextra -pedantic -Wshadow -Wfloat-equal -Wconversion -Wlogical-op -D_GLIBCXX_DEBUG -o $@ $^
.PRECIOUS: %.o

%.out: %.o
	./$^

%.: %.o
	for u in $**n; do echo - $$u; ./$^ < $$u; done""",
}
for i, sample in enumerate(problem["samples"]):
    files["A%d.in" % (i + 1)] = sample["input"]
