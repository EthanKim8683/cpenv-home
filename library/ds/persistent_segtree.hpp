// https://usaco.guide/adv/persistent#persistent-segment-tree
// https://github.com/atcoder/ac-library/blob/master/atcoder/segtree.hpp
template <class S, auto op, auto e>
struct persistent_segtree {
  static_assert(std::is_convertible_v<decltype(op), std::function<S(S, S)>>,
                "op must work as S(S, S)");
  static_assert(std::is_convertible_v<decltype(e), std::function<S()>>,
                "e must work as S()");

 private:
  struct node {
    S v;
    node *l, *r;

    node(S _v) : v(_v), l(nullptr), r(nullptr) {}
    node(node *_l, node *_r) : v(e()), l(_l), r(_r) {
      if (l != nullptr) {
        v = op(v, l->v);
      }
      if (r != nullptr) {
        v = op(v, r->v);
      }
    }
  };

  int n;
  node *root;

  persistent_segtree(int _n, node *_root) : n(_n), root(_root) {}

 public:
  persistent_segtree() {}
  persistent_segtree(const std::vector<S> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (r - l == 1) return new node(v[l]);

      int m = l + (r - l) / 2;
      return new node(self(self, l, m), self(self, m, r));
    };
    root = dfs(dfs, 0, n);
  }
  persistent_segtree(int _n) : persistent_segtree(std::vector<S>(_n, e())) {}

  persistent_segtree<S, op, e> set(int i, S v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (r - l == 1) return new node(v);

      int m = l + (r - l) / 2;
      if (i < m) {
        return new node(self(self, a->l, l, m), a->r);
      } else {
        return new node(a->l, self(self, a->r, m, r));
      }
    };
    return {n, dfs(dfs, root, 0, n)};
  }

  S get(int i) const {
    node *a = root;
    int l = 0, r = n;
    while (r - l > 1) {
      int m = l + (r - l) / 2;
      if (i < m) {
        a = a->l;
        r = m;
      } else {
        a = a->r;
        l = m;
      }
    }
    return a->v;
  }

  S prod(int l, int r) const {
    auto dfs = [&](auto self, node *a, int l2, int r2) -> S {
      if (r <= l2 or r2 <= l) return e();
      if (l <= l2 and r2 <= r) return a->v;

      int m = l2 + (r2 - l2) / 2;
      return op(self(self, a->l, l2, m), self(self, a->r, m, r2));
    };
    return dfs(dfs, root, 0, n);
  }

  S all_prod() const { return root->v; }

  template <bool (*f)(S)>
  int max_right(int l) const {
    return max_right(l, [](S x) { return f(x); });
  }

  template <class F>
  int max_right(int l, F f) const {
    S v = e();
    auto dfs = [&](auto self, node *a, int l2, int r2) -> int {
      if (r2 <= l) return r2;
      if (l <= l2 and f(op(v, a->v))) {
        v = op(v, a->v);
        return r2;
      }
      if (r2 - l2 == 1) return l2;

      int m = l2 + (r2 - l2) / 2, r = self(self, a->l, l2, m);
      if (r != m) return r;
      return self(self, a->r, m, r2);
    };
    return dfs(dfs, root, 0, n);
  }

  template <bool (*f)(S)>
  int min_left(int r) const {
    return min_left(r, [](S x) { return f(x); });
  }

  template <class F>
  int min_left(int r, F f) const {
    S v = e();
    auto dfs = [&](auto self, node *a, int l2, int r2) -> int {
      if (r <= l2) return l2;
      if (r2 <= r and f(op(a->v, v))) {
        v = op(a->v, v);
        return l2;
      }
      if (r2 - l2 == 1) return r2;

      int m = l2 + (r2 - l2) / 2, l = self(self, a->r, m, r2);
      if (l != m) return l;
      return self(self, a->l, l2, m);
    };
    return dfs(dfs, root, 0, n);
  }
};
