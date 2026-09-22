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

// TODO: replace size with a general property generic
template <class T>
struct implicit_treap {
 private:
  static std::mt19937 rng;

  struct node {
    T v;
    node *l, *r;
    int size;

    node(T _v) : v(_v), l(nullptr), r(nullptr), size(0) {}
  };

  node *root;

  static int safe_size(node *a) { return a == nullptr ? 0 : a->size; }

  static void safe_pull(node *a) {
    if (a == nullptr) return;
    a->size = safe_size(a->l) + 1 + safe_size(a->r);
  }

  static node *build(const std::vector<T> &v) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (l == r) return nullptr;
      int m = l + (r - l) / 2;
      node *a = new node(v[m]);
      a->l = self(self, l, m);
      a->r = self(self, m + 1, r);
      safe_pull(a);
      return a;
    };
    return dfs(dfs, 0, v.size());
  }

  static node *merge(node *l, node *r) {
    if (l == nullptr) return r;
    if (r == nullptr) return l;
    if (rng() % (safe_size(l) + safe_size(r)) < safe_size(l)) {
      l = new node(*l);
      l->r = merge(l->r, r);
      safe_pull(l);
      return l;
    } else {
      r = new node(*r);
      r->l = merge(l, r->l);
      safe_pull(r);
      return r;
    }
  }

  static std::pair<node *, node *> split(node *a, int i) {
    if (a == nullptr) return {nullptr, nullptr};
    if (i <= safe_size(a->l)) {
      auto [l, r] = split(a->l, i);
      a = new node(*a);
      a->l = r;
      safe_pull(a);
      return {l, a};
    } else {
      auto [l, r] = split(a->r, i - (safe_size(a->l) + 1));
      a = new node(*a);
      a->r = l;
      safe_pull(a);
      return {a, r};
    }
  }

  node *get_node(int i) {
    assert(0 <= i and i < size());
    auto dfs = [&](auto self, node *a, int i) -> node * {
      if (i == safe_size(a->l)) {
        return a;
      } else if (i < safe_size(a->l)) {
        return self(self, a->l, i);
      } else {
        return self(self, a->r, i - (1 + safe_size(a->l)));
      }
    };
    return dfs(dfs, root, i);
  };

 public:
  implicit_treap() : root(nullptr) {}

  implicit_treap(const std::vector<T> &v) : root(build(v)) {}

  implicit_treap(int n, T v) : implicit_treap(std::vector<T>(n, v)) {}

  int size() const { return safe_size(root); }

  T get(int i) { return get_node(i)->v; }

  void transition(int x) {
    auto [l1, r1] = split(root, x);
    auto [l2, r2] = split(r1, x);
    root = merge(l2, root);
  }
};
template <class T>
std::mt19937 implicit_treap<T>::rng(time(nullptr));

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vi A(N);
  for (auto &e : A) cin >> e;

  // vi results(2 * N + 1);
  // iota(all(results), 0);
  // for (int i = N - 1; i >= 0; i--) {
  //   vi prefix(results.begin() + A[i], results.begin() + 2 * A[i]);
  //   results.insert(results.begin(), all(prefix));
  //   cout << results[0] << ' ';
  // }

  vi v(2 * N);
  iota(all(v), 0);
  implicit_treap<int> tr(v);
  for (int i = N - 1; i >= 0; i--) {
    tr.transition(A[i]);
    cout << tr.get(0) << ' ';
  }
}
