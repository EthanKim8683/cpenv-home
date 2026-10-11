// https://jilljenn.github.io/tryalgo/_modules/tryalgo/union_rectangles.html#union_rectangles
template <class S, class T>
struct cover_query {
 private:
  struct seg {
    T c;
    S s, w;
  };

  int n;
  std::vector<seg> data;

 public:
  cover_query() {}
  cover_query(const std::vector<S> &l)
      : n(1 << std::__lg(2 * l.size() - 1)), data(2 * n, {0, 0, 0}) {
    for (int i = 0; i < l.size(); i++) {
      data[n + i].w = l[i];
    }
    for (int i = n - 1; i > 0; i--) {
      data[i].w = data[i << 1].w + data[i << 1 | 1].w;
    }
  }
  cover_query(int _n) : cover_query(std::vector<S>(_n, 1)) {}

  S cover() { return data[1].s; }

  void add(int l, int r, T dc) {
    auto dfs = [&](auto self, int i, int sl, int sr) -> void {
      if (sr <= l or r <= sl) return;
      if (l <= sl and sr <= r) {
        data[i].c += dc;
      } else {
        int sm = sl + (sr - sl) / 2;
        self(self, i << 1, sl, sm);
        self(self, i << 1 | 1, sm, sr);
      }
      if (data[i].c == 0) {
        if (i >= n) {
          data[i].s = 0;
        } else {
          data[i].s = data[i << 1].s + data[i << 1 | 1].s;
        }
      } else {
        data[i].s = data[i].w;
      }
    };
    dfs(dfs, 1, 0, n);
  }
};
