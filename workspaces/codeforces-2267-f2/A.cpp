#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <assert.h>
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

const int MAXK = 1e7;

struct trie {
  struct node {
    array<int, 2> adj;
    int count;

    node() : adj({-1, -1}), count(0) {}
  };

  node nodes[MAXK];
  int k = 0;

  int new_node() {
    nodes[k] = node();
    return k++;
  }

  int node_like(int a) {
    nodes[k] = nodes[a];
    return k++;
  }

  int insert(int a, int x, int n) {
    a = node_like(a);
    nodes[a].count += 1;

    if (n >= 0) {
      int &b = nodes[a].adj[x >> n & 1];
      if (b == -1) {
        b = new_node();
      }
      b = insert(b, x, n - 1);
    }
    return a;
  }

  int erase(int a, int x, int n) {
    if (nodes[a].count == 1) return -1;

    a = node_like(a);
    nodes[a].count -= 1;

    if (n >= 0) {
      int &b = nodes[a].adj[x >> n & 1];
      b = erase(b, x, n - 1);
    }
    return a;
  }

  bool empty(int a) { return nodes[a].adj[0] == -1 and nodes[a].adj[1] == -1; }

  int match(int a, int x, int n) {
    if (n < 0) return 0;

    int d = x >> n & 1;
    if (nodes[a].adj[d] == -1) {
      return match(nodes[a].adj[d ^ 1], x, n - 1) ^ (d ^ 1) << n;
    } else {
      return match(nodes[a].adj[d], x, n - 1) ^ d << n;
    }
  }

  void clear() { k = 0; }
};

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  //

  int T;
  cin >> T;

  trie tr;
  while (T--) {
    int N, Q;
    cin >> N >> Q;

    vi A(N);
    for (auto &e : A) cin >> e;

    vi ans;
    while (count(all(A), 0) != N) {
      ans.pb(*max_element(all(A)) - *min_element(all(A)));
      tr.clear();
      vi roots(N);
      roots[0] = tr.new_node();
      rep(i, 1, N) { roots[i] = tr.insert(roots[i - 1], A[i - 1], 30 - 1); }
      priority_queue<pii> pq;
      auto nudge = [&](int i) -> void {
        if (roots[i] == -1 or tr.empty(roots[i])) return;
        int x = tr.match(roots[i], A[i], 30 - 1);
        roots[i] = tr.erase(roots[i], x, 30 - 1);
        pq.emplace(-(A[i] ^ x), i);
      };
      rep(i, 0, N) { nudge(i); }
      vi A2;
      rep(i, 0, N) {
        auto [x, j] = pq.top();
        pq.pop();
        A2.pb(-x);
        nudge(j);
      }
      A = A2;
    }
    while (Q--) {
      int X;
      cin >> X;

      if (X >= sz(ans)) {
        cout << "0\n";
      } else {
        cout << ans[X] << '\n';
      }
    }
  }
}
