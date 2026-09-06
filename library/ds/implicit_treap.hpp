// TODO: replace size with a general property generic
template <class T>
struct implicit_treap {
 private:
  static std::mt19937 rng;

  struct node {
    T v;
    node *l, *r;
    int y, size;

    node(T _v, int _y) : v(_v), l(nullptr), r(nullptr), y(_y), size(0) {}
    node(T _v) : node(_v, rng()) {}
  };

  node *root;

  static int safe_size(node *a) { return a == nullptr ? 0 : a->size; }

  static node *safe_copy(node *a) {
    if (a == nullptr) return nullptr;
    node *a2 = new node(*a);
    a2->l = safe_copy(a->l);
    a2->r = safe_copy(a->r);
    return a2;
  }

  static void safe_free(node *a) {
    if (a == nullptr) return;
    safe_free(a->l);
    safe_free(a->r);
    free(a);
  }

  static void safe_pull(node *a) {
    if (a == nullptr) return;
    a->size = safe_size(a->l) + 1 + safe_size(a->r);
  }

  static node *merge(node *l, node *r) {
    auto dfs = [&](auto self, node *&a, node *l, node *r) -> void {
      if (l == nullptr) {
        a = r;
      } else if (r == nullptr) {
        a = l;
      } else if (l->y >= r->y) {
        self(self, l->r, l->r, r);
        a = l;
      } else {
        self(self, r->l, l, r->l);
        a = r;
      }
      safe_pull(a);
    };
    node *rv;
    dfs(dfs, rv, l, r);
    return rv;
  }

  static std::pair<node *, node *> split(node *a, int i) {
    auto dfs = [&](auto self, node *a, node *&l, node *&r, int i) -> void {
      if (a == nullptr) {
        l = r = nullptr;
        return;
      }
      if (i <= safe_size(a->l)) {
        self(self, a->l, l, a->l, i);
        r = a;
      } else {
        self(self, a->r, a->r, r, i - (1 + safe_size(a->l)));
        l = a;
      }
      safe_pull(a);
    };
    node *l, *r;
    dfs(dfs, a, l, r, i);
    return {l, r};
  }

  implicit_treap(node *_root) : root(_root) {}

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

  implicit_treap(const std::vector<int> &v) {
    auto dfs_heapify = [&](auto self, node *a) -> void {
      if (a == nullptr) return;
      node *b = a;
      if (a->l != nullptr and a->l->y > b->y) {
        b = a->l;
      }
      if (a->r != nullptr and a->r->y > b->y) {
        b = a->r;
      }
      if (b != a) {
        std::swap(a->y, b->y);
        self(self, b);
      }
    };

    auto dfs_build = [&](auto self, int l, int r) -> node * {
      if (l == r) return nullptr;
      int m = l + (r - l) / 2;
      node *a = new node(v[m]);
      a->l = self(self, l, m);
      a->r = self(self, m + 1, r);
      dfs_heapify(dfs_heapify, a);
      safe_pull(a);
      return a;
    };
    root = dfs_build(dfs_build, 0, v.size());
  }

  implicit_treap(int n, T v) : implicit_treap(std::vector<T>(n, v)) {}

  ~implicit_treap() { safe_free(root); }

  int size() const { return safe_size(root); }

  void insert(int i, T v) {
    assert(0 <= i and i <= size());
    auto [l, r] = split(root, i);
    root = merge(merge(l, new node(v)), r);
  }

  void erase(int i) {
    assert(0 <= i and i < size());
    auto [l1, r1] = split(root, i);
    auto [l2, r2] = split(r1, 1);
    safe_free(l2);
    root = merge(l1, r2);
  }

  void set(int i, T v) { get_node(i)->v = v; }

  T get(int i) { return get_node(i)->v; }
};
template <class T>
std::mt19937 implicit_treap<T>::rng(time(nullptr));
