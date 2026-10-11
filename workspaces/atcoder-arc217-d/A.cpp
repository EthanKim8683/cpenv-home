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

// TODO: replace size with a general property generic
template <class T>
struct implicit_treap {
 private:
  static std::mt19937 rng;

  struct node {
    T v;
    std::shared_ptr<node> l, r;
    int size, n, nsum;

    node(T _v, int _n)
        : v(_v), l(nullptr), r(nullptr), size(1), n(_n), nsum(n) {}
  };

  std::shared_ptr<node> root;
  int m;

  static int safe_size(std::shared_ptr<node> a) {
    return a == nullptr ? 0 : a->size;
  }

  static int safe_nsum(std::shared_ptr<node> a) {
    return a == nullptr ? 0 : a->nsum;
  }

  static void safe_pull(std::shared_ptr<node> a) {
    if (a == nullptr) return;
    a->size = safe_size(a->l) + 1 + safe_size(a->r);
    a->nsum = safe_nsum(a->l) + a->n + safe_nsum(a->r);
  }

  static std::shared_ptr<node> merge(std::shared_ptr<node> l,
                                     std::shared_ptr<node> r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (rng() % (safe_size(l) + safe_size(r)) < safe_size(l)) {
      l = std::make_shared<node>(*l);
      l->r = merge(l->r, r);
      safe_pull(l);
      return l;
    } else {
      r = std::make_shared<node>(*r);
      r->l = merge(l, r->l);
      safe_pull(r);
      return r;
    }
  }

  static std::pair<std::shared_ptr<node>, std::shared_ptr<node>> split(
      std::shared_ptr<node> a, int i) {
    if (a == nullptr) return {nullptr, nullptr};
    if (i < safe_nsum(a->l)) {
      auto [l, r] = split(a->l, i);
      a = std::make_shared<node>(*a);
      a->l = r;
      safe_pull(a);
      return {l, a};
    } else if (i < safe_nsum(a->l) + a->n) {
      std::shared_ptr<node> l = a->l;
      if (safe_nsum(a->l) < i) {
        l = std::make_shared<node>(a->v, i - safe_nsum(a->l));
        l->l = a->l;
        safe_pull(l);
      }
      std::shared_ptr<node> r =
          std::make_shared<node>(a->v, (safe_nsum(a->l) + a->n) - i);
      r->r = a->r;
      safe_pull(r);
      return {l, r};
    } else {
      auto [l, r] = split(a->r, i - (safe_nsum(a->l) + a->n));
      a = std::make_shared<node>(*a);
      a->r = l;
      safe_pull(a);
      return {a, r};
    }
  }

 public:
  implicit_treap(int _m) : root(nullptr), m(_m) {}

  void append(T v, int n) { root = merge(root, std::make_shared<node>(v, n)); }

  void transition(int x) {
    auto [l1, r1] = split(root, x);
    auto [l2, r2] = split(root, m + 1 - x);
    root = merge(l1, l2);
  }

  vc<std::shared_ptr<node>> nodes() {
    vc<std::shared_ptr<node>> rv;
    auto dfs = [&](auto self, std::shared_ptr<node> a) -> void {
      if (a == nullptr) return;
      self(self, a->l);
      rv.pb(a);
      self(self, a->r);
    };
    dfs(dfs, root);
    return rv;
  }
};
template <class T>
std::mt19937 implicit_treap<T>::rng(time(nullptr));

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

    vi A(N);
    for (auto &e : A) cin >> e;

    // vc<bool> dp(M + 1);
    // dp[0] = true;
    // for (int i = N - 1; i >= 0; i--) {
    //   vc<bool> dp2;
    //   rep(j, 0, A[i]) { dp2.pb(dp[j]); }
    //   dp2.insert(dp2.end(), all(dp));
    //   dp2.resize(M + 1);
    //   dp = dp2;
    // }
    // int ans = 0, x = 0;
    // rep(i, 0, M + 1) {
    //   if (dp[i]) {
    //     x = i;
    //   }
    //   ans ^= i * x;
    // }
    // cout << ans << '\n';

    implicit_treap<bool> tr(M);
    tr.append(true, 1);
    tr.append(false, M);
    for (int i = N - 1; i >= 0; i--) {
      tr.transition(A[i]);
    }
    int ans = 0, i = 0, x = 0;
    for (auto e : tr.nodes()) {
      if (e->v) {
        x = i;
      }
      rep(j, 0, e->n) {
        if (i > M) goto SKIP;
        ans ^= i * x;
        i++;
      }
    }
  SKIP:
    cout << ans << '\n';
  }
}
