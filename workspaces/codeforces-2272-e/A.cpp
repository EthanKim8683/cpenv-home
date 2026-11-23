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

  //

  int T;
  cin >> T;

  while (T--) {
    int N, M;
    cin >> N >> M;

    string S;
    cin >> S;

    string T;
    cin >> T;

    auto solve = [&](string S, string T) -> vi {
      int N = sz(S), M = sz(T);

      vi index(M, -1);
      rep(i, 0, M) {
        if (T[i] == 'W') {
          index[i] = i;
        }
      }
      rep(i, 0, M - 1) { chmax(index[i + 1], index[i]); }

      if (find(all(S), 'W') == S.end()) {
        vi ans;
        rep(i, 0, M) {
          if (T[i] != 'R') continue;
          if (index[i] == -1) {
            ans.pb(1);
          } else {
            ans.pb(N + 1);
          }
        }
        return ans;
      }

      int tail = 1;
      while (S[N - tail] == 'R') {
        tail++;
      }

      queue<int> q;
      vi dist(N + M, INF);
      auto push = [&](int d, int a) -> void {
        if (a >= N + M or d >= dist[a]) return;
        dist[a] = d;
        q.push(a);
      };
      rep(i, 0, N) {
        if (S[i] != 'W') continue;
        push(0, i);
      }

      vi ans;
      int count = 1;
      rep(i, 0, M) {
        if (T[i] != 'R') continue;
        if (index[i] == -1) {
          while (sz(q) > 0) {
            int a = q.front();
            if (dist[a] > i) break;
            q.pop();
            count++;
            push(dist[a] + 1, a + 1);
          }
          ans.pb(count);
        } else {
          ans.pb((N + i - min(tail, i - index[i]) + 1) - index[i]);
        }
      }
      return ans;
    };
    for (auto e : solve(T, S)) {
      cout << e << ' ';
    }
    cout << '\n';
    for (auto e : solve(S, T)) {
      cout << e << ' ';
    }
    cout << '\n';
  }
}
