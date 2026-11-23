struct trie {
  struct node {
    int ch[2]{};
  };
  vc<node> d;
  trie() : d(1) {}
  int ensure(int &a) { return a ?: (a = sz(d), d.eb(), sz(d) - 1); }
  void add(int x) {
    for (int i = 60, a = 0; i--;) {
      a = ensure(d[a].ch[x >> i & 1]);
    }
  }
  int get(int ps) {
    int a = 0;
    for (int i = 60; i--;) {
      if (!(a = d[a].ch[ps >> i & 1])) return -1;
    }
    return a;
  }
};
