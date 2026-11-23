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
    int N, K;
    cin >> N >> K;

    deque<int> dq;
    rep(i, 0, N) { dq.pb(i); }
    vi front, back;
    bool reversed = true;
    while (sz(dq) > 0) {
      if (sz(dq) >= 2 and (sz(dq) == N or 2 * (sz(dq) - 1) <= K)) {
        K -= 2 * (sz(dq) - 1);
        reversed = not reversed;
        if (reversed) {
          back.pb(dq.front());
          dq.pop_front();
          front.pb(dq.back());
          dq.pop_back();
        } else {
          front.pb(dq.front());
          dq.pop_front();
          back.pb(dq.back());
          dq.pop_back();
        }
      } else {
        if (reversed) {
          back.pb(dq.front());
          dq.pop_front();
        } else {
          front.pb(dq.front());
          dq.pop_front();
        }
      }
    }
    if (K != 0) {
      cout << "-1\n";
      continue;
    }
    reverse(all(back));
    vi order = front;
    order.insert(order.end(), all(back));
    // for (auto e : order) {
    //   cerr << e + 1 << ' ';
    // }
    // cerr << '\n';
    rep(i, 0, N - 1) {
      cout << order[i] + 1 << ' ' << order[i + 1] + 1 << '\n';
    }
  }
}
