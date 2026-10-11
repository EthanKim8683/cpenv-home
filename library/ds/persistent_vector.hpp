// https://usaco.guide/adv/persistent#path-copying
// Persistent array with insertion and deletion
template <class T>
struct persistent_vector {
 private:
  struct node {
    T v;
    node *l, *r;

    node() : v(), l(nullptr), r(nullptr) {}
    node(T _v) : v(_v), l(nullptr), r(nullptr) {}
    node(T _v, node *_l, node *_r) : v(_v), l(_l), r(_r) {}
  };

  int n;
  node *root;

  persistent_vector(int _n, node *_root) : n(_n), root(_root) {}

  static int middle(int l, int r) {
    return l + (1 << std::__lg(r - l + 1)) - 1;
  }

 public:
  persistent_vector() : n(0), root(nullptr) {}

  persistent_vector(const std::vector<T> &v) : n(v.size()) {
    auto dfs = [&](auto self, int l, int r) -> node * {
      if (l > r) return nullptr;

      int m = middle(l, r);
      return new node(v[m], self(self, l, m - 1), self(self, m + 1, r));
    };
    root = dfs(dfs, 0, n - 1);
  }
  persistent_vector(int _n, T nil = T())
      : persistent_vector(std::vector<T>(_n, nil)) {}

  int size() const { return n; }
  bool empty() const { return n == 0; }

  persistent_vector<T> set(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == i) return new node(v, a->l, a->r);

      if (i < m) {
        return new node(a->v, self(self, a->l, l, m - 1), a->r);
      } else {
        return new node(a->v, a->l, self(self, a->r, m + 1, r));
      }
    };
    return {n, dfs(dfs, root, 0, n - 1)};
  }

  T get(int i) const {
    node *a = root;
    int l = 0, r = n - 1;
    while (true) {
      int m = middle(l, r);
      if (m == i) return a->v;

      if (i < m) {
        a = a->l;
        r = m - 1;
      } else {
        a = a->r;
        l = m + 1;
      }
    }
  }

  // O(\log(N))
  persistent_vector<T> push_back(T v) {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return new node(v);

      int m = middle(l, r);
      if (m - l == r - m) return new node(v, a, nullptr);

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n + 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log(N))
  persistent_vector<T> pop_back() {
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      int m = middle(l, r);
      if (m == r) return a->l;

      return new node(a->v, a->l, self(self, a->r, m + 1, r));
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }

  // O(\log(N+K))
  persistent_vector<T> insert(int i, T v) {
    auto dfs = [&](auto self, node *a, int l, int r, bool check) -> node * {
      if (check) {
        if (l > r) return new node(v);
      } else {
        if (l > r) return nullptr;
        if (r < i) return a;
      }

      int m = middle(l, r);
      bool push = false;
      if (check) {
        push = m - l == r - m;
        check = push == false;
      }

      node *a2 = new node(a->v);
      a2->l = self(self, a->l, l, m - 1, false);
      if (m >= i) {
        a2->v = v;
        v = a->v;
      }
      a2->r = self(self, a->r, m + 1, r, check);

      if (push) {
        return new node(v, a2, nullptr);
      } else {
        return a2;
      }
    };
    return {n + 1, dfs(dfs, root, 0, n - 1, true)};
  }

  // O(\log(N+K))
  persistent_vector<T> erase(int i) {
    T v;
    auto dfs = [&](auto self, node *a, int l, int r) -> node * {
      if (l > r) return nullptr;
      if (r < i) return a;

      int m = middle(l, r);
      if (m == n - 1) {
        v = a->v;
        return self(self, a->l, l, m - 1);
      }

      node *a2 = new node(a->v);
      a2->r = self(self, a->r, m + 1, r);
      if (m >= i) {
        a2->v = v;
        v = a->v;
      }
      a2->l = self(self, a->l, l, m - 1);
      return a2;
    };
    return {n - 1, dfs(dfs, root, 0, n - 1)};
  }
};
