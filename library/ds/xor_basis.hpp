template <class T>
struct xor_basis {
 private:
  int n, m;
  std::vector<T> basis;

 public:
  xor_basis(int _n) : n(_n), m(0), basis(n, 0) {}
  xor_basis() : xor_basis(8 * sizeof(T)) {}

  bool insert(T x) {
    for (int i = n - 1; i >= 0; i--) {
      if (~x >> i & 1) continue;
      if (basis[i] == 0) {
        for (int j = 0; j < i; j++) {
          if (~x >> j & 1) continue;
          x ^= basis[j];
        }
        basis[i] = x;
        m++;
        for (int j = i + 1; j < n; j++) {
          if (~basis[j] >> i & 1) continue;
          basis[j] ^= x;
        }
        return true;
      }
      x ^= basis[i];
    }
    return false;
  }

  T size() { return m; }

  bool contains(T x) {
    for (int i = 0; i < n; i++) {
      if (~x >> i & 1) continue;
      if (basis[i] == 0) return false;
      x ^= basis[i];
    }
    return true;
  }

  T order_of_key(T x) {
    int x2 = 0, j = m - 1, rv = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (basis[i] == 0) continue;
      if ((x2 ^ basis[i]) <= x) {
        rv += 1 << j;
        x2 ^= basis[i];
      }
      j--;
    }
    return rv;
  }

  T find_by_order(T k) {
    int k2 = 0, j = m - 1, rv = 0;
    for (int i = n - 1; i >= 0; i--) {
      if (basis[i] == 0) continue;
      if (k2 + (1 << j) <= k) {
        rv ^= basis[i];
        k2 += 1 << j;
      }
      j--;
    }
    return rv;
  }
};
