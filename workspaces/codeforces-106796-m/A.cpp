#ifndef TEMPLATE_H
#define TEMPLATE_H
#include <bits/stdc++.h>

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/rope>
using namespace __gnu_pbds;
using namespace __gnu_cxx;
#pragma GCC optimize("O3,unroll-loops")
// #pragma GCC target("avx,fma,avx2,bmi,bmi2,lzcnt,popcnt")
#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#define putchar_unlocked _putchar_nolock
#endif
using namespace std;
namespace misc_macro {
using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vll = vector<ll>;
using vvll = vector<vll>;
using vi = vector<int>;
using vvi = vector<vi>;
using pi = pair<int, int>;
using pll = pair<ll, ll>;
using vpi = vector<pi>;
using vpll = vector<pll>;
using vvpi = vector<vpi>;
using vvpll = vector<vpll>;
using i128 = __int128;
template <typename T>
using priority_queueMin = priority_queue<T, vector<T>, greater<T>>;
template <typename T, typename V>
using ordered_set =
    tree<T, null_type, V, rb_tree_tag, tree_order_statistics_node_update>;
constexpr auto rmax = ranges::max;
constexpr auto rmin = ranges::min;
constexpr auto rsort = ranges::sort;
constexpr auto rreverse = ranges::reverse;
constexpr auto rcount = ranges::count;
constexpr auto runique = ranges::unique;
constexpr auto rlower = ranges::lower_bound;
constexpr auto rupper = ranges::upper_bound;
constexpr auto rcopy = ranges::copy;
constexpr auto rfind = ranges::find;
constexpr auto ris_sorted = ranges::is_sorted;
constexpr auto chmax(auto &val, auto c) {
  if (c > val) val = c;
}
constexpr auto chmin(auto &val, auto c) {
  if (c < val) val = c;
}
constexpr ll INF = 1ll << 60;
}  // namespace misc_macro
using namespace misc_macro;
#define all(x) begin(x), end(x)
#define endl "\n"
char _;
void scan(integral auto &x);
void scan(string &s);
void scan(char *s);
void scan(auto &x, auto &...res) {
  scan(x);
  scan(res...);
}
void scarr(auto &&ptr) {
  for (auto &i : ptr) scan(i);
}
void pint(auto val) {
  if (val == 0) {
    putchar_unlocked('0');
    return;
  }
  static char buffer[50];
  static int ptr = 0;
  static bool neg;
  neg = false;
  if (val < 0) {
    neg = true;
    val = -val;
  }
  while (val > 0) {
    buffer[++ptr] = val % 10 + '0';
    val /= 10;
  }
  if (neg) putchar_unlocked('-');
  while (ptr > 0) {
    putchar_unlocked(buffer[ptr--]);
  }
}

#define sqr(x) ((x) * (x))
#ifndef ONLINE_JUDGE
#define debug(...) \
  cout << "dbg: [" << #__VA_ARGS__ << "] = ", debug_impl(__VA_ARGS__)
#else
#define debug(...)
#endif

template <typename T, typename U>
ostream &operator<<(ostream &os, const pair<T, U> &p) {
  cout << p.first << ' ' << p.second;
  return os;
}

template <typename T>
concept is_string_like = convertible_to<T, string_view>;

template <ranges::range R>
  requires(!is_string_like<R>) && (!ranges::range<ranges::range_value_t<R>> ||
                                   is_string_like<ranges::range_value_t<R>>)
ostream &operator<<(ostream &os, const R &x) {
  for (const auto &i : x) {
    os << i << ' ';
  }
  return os;
}

template <ranges::range R>
  requires(!is_string_like<R>) && ranges::range<ranges::range_value_t<R>> &&
          (!is_string_like<ranges::range_value_t<R>>)
ostream &operator<<(ostream &os, const R &x) {
  for (const auto &i : x) {
    os << i << '\n';
  }
  return os;
}

template <typename T>
void debug_impl(const T &A) {
  cout << A << '\n';
}

template <typename T, typename... U>
void debug_impl(const T &A, const U &...B) {
  cout << A << ' ';
  debug_impl(B...);
}

struct custom_hash {
  static ull splitmix64(uint64_t x) {
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
  }

  ull operator()(ull x) const {
    static const ull FIXED_RANDOM =
        chrono::steady_clock::now().time_since_epoch().count();
    return splitmix64(x + FIXED_RANDOM);
  }
};

struct SplitMix64PRNG {
  ull state;

  SplitMix64PRNG() {
    state = std::chrono::steady_clock::now().time_since_epoch().count();
  }

  ull next() {
    // http://xorshift.di.unimi.it/splitmix64.c
    state += 0x9e3779b97f4a7c15;
    ull z = state;
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
    z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
    return (z ^ (z >> 31));
  }
};

namespace mmath {
template <typename U, U mod>
struct mint;
template <typename U, typename V, typename W>
constexpr U fpow(U a, V n, W p);
template <typename U, typename V>
constexpr U modinv(U a, const V &p);
template <typename U>
struct mint_runtime;
class lpf;
template <int N, ll mod>
struct fiTable;
template <int N, ll P, ll mod>
struct pTable;

template <typename U, U mod>
struct mint {
  U val = 0;
#define MINT_IMPL(M)                                                           \
  constexpr M(U v) {                                                           \
    val = v % mod;                                                             \
    if (val < 0) val += mod;                                                   \
  }                                                                            \
  constexpr M() { val = 0; }                                                   \
  constexpr M(const M &) = default;                                            \
  constexpr M operator+(const M &other) const {                                \
    return M((val + other.val) % mod);                                         \
  }                                                                            \
  constexpr M operator+(const U other) const {                                 \
    return M((val + other) % mod);                                             \
  }                                                                            \
  friend constexpr M operator+(const U other, M rhs) {                         \
    return M((rhs.val + other) % mod);                                         \
  }                                                                            \
  constexpr M operator-(const M &other) const {                                \
    return M((val + (mod - other.val)) % mod);                                 \
  }                                                                            \
  constexpr M operator-(const U other) const {                                 \
    return M((val + (mod - other)) % mod);                                     \
  }                                                                            \
  friend constexpr M operator-(const U other, M rhs) {                         \
    return M((other + (mod - rhs.val)) % mod);                                 \
  }                                                                            \
  constexpr M operator*(const M &other) const {                                \
    return M((val * other.val) % mod);                                         \
  }                                                                            \
  constexpr M operator*(const U other) const {                                 \
    return M((val * other) % mod);                                             \
  }                                                                            \
  friend constexpr M operator*(const U other, M rhs) {                         \
    return M((rhs.val * other) % mod);                                         \
  }                                                                            \
  constexpr M pow(M &other) const { return M(fpow(val, other.val, mod)); }     \
  constexpr M pow(U other) const { return M(fpow(val, other, mod)); }          \
  constexpr M operator/(const M &other) const {                                \
    return M(val * modinv(other.val, mod) % mod);                              \
  }                                                                            \
  constexpr M operator/(const U other) const {                                 \
    return M(val * modinv(other, mod) % mod);                                  \
  }                                                                            \
  friend constexpr M operator/(const U other, M rhs) {                         \
    return M(other * modinv(rhs.val, mod) % mod);                              \
  }                                                                            \
  constexpr M &operator+=(const M &other) {                                    \
    val = (val + other.val) % mod;                                             \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator+=(const U &other) {                                    \
    val = (val + other) % mod;                                                 \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator-=(const M &other) {                                    \
    val -= other.val;                                                          \
    if (val < 0) val += mod;                                                   \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator-=(const U &other) {                                    \
    val -= other;                                                              \
    if (val < 0) val += mod;                                                   \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator*=(const M &other) {                                    \
    val = val * other.val % mod;                                               \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator*=(const U other) {                                     \
    val = val * other % mod;                                                   \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator/=(const M &other) {                                    \
    val = val * modinv(other.val, mod) % mod;                                  \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator/=(const U other) {                                     \
    val = val * modinv(other, mod) % mod;                                      \
    return *this;                                                              \
  }                                                                            \
  friend ostream &operator<<(ostream &os, const M &x) { return os << x.val; }  \
  friend istream &operator>>(istream &is, M &x) {                              \
    is >> x.val;                                                               \
    x.val %= mod;                                                              \
    if (x.val < 0) x.val += mod;                                               \
    return is;                                                                 \
  }                                                                            \
  constexpr M &operator=(U v) {                                                \
    val = v % mod;                                                             \
    if (val < 0) val += mod;                                                   \
    return *this;                                                              \
  }                                                                            \
  constexpr M &operator=(const M &other) {                                     \
    val = other.val % mod;                                                     \
    if (val < 0) val += mod;                                                   \
    return *this;                                                              \
  }                                                                            \
  constexpr bool operator<(const M &other) const { return val < other.val; }   \
  constexpr bool operator<=(const M &other) const { return val <= other.val; } \
  constexpr bool operator==(const M &other) const { return val == other.val; } \
  constexpr bool operator>(const M &other) const { return val > other.val; }   \
  constexpr bool operator>=(const M &other) const { return val >= other.val; } \
  constexpr bool operator<(const U &other) const { return val < other; }       \
  constexpr bool operator<=(const U &other) const { return val <= other; }     \
  constexpr bool operator==(const U &other) const { return val == other; }     \
  constexpr bool operator>(const U &other) const { return val > other; }       \
  constexpr bool operator>=(const U &other) const { return val >= other; }     \
  friend constexpr bool operator<(const U &other, const M &rhs) {              \
    return other < rhs.val;                                                    \
  }                                                                            \
  friend constexpr bool operator<=(const U &other, const M &rhs) {             \
    return other <= rhs.val;                                                   \
  }                                                                            \
  friend constexpr bool operator==(const U &other, const M &rhs) {             \
    return other == rhs.val;                                                   \
  }                                                                            \
  friend constexpr bool operator>(const U &other, const M &rhs) {              \
    return other > rhs.val;                                                    \
  }                                                                            \
  friend constexpr bool operator>=(const U &other, const M &rhs) {             \
    return other >= rhs.val;                                                   \
  }
  MINT_IMPL(mint)
};

template <typename U>
struct mint_runtime {
  inline static U mod;
  U val = 0;
  void setMod(U m) { mod = m; }
  MINT_IMPL(mint_runtime)
};

template <typename U, typename V, typename W>
constexpr U fpow(U a, V n, W p) {
  U res = 1;
  U mult = a;
  while (n) {
    if (n & 1) res = (res * mult) % p;
    mult = (mult * mult) % p;
    n >>= 1;
  }
  return res;
}

template <typename U, typename V>
constexpr U modinv(U a, const V &p) {
  return fpow(a, p - 2, p);
}

class lpf {
  vi lowest_prime;

 public:
  lpf(int n) {
    lowest_prime = vi(n + 1, 0);
    for (ll i = 2; i <= n; i++) {
      if (lowest_prime[i] != 0) continue;
      lowest_prime[i] = i;
      for (ll j = i * i; j <= n; j += i) {
        if (lowest_prime[j] == 0) {
          lowest_prime[j] = i;
        }
      }
    }
  }
  int &operator[](int idx) { return lowest_prime[idx]; }
  bool isprime(int idx) const { return idx == lowest_prime[idx]; }
};

template <int N, ll mod>
struct fiTable {
  mint<ll, mod> fact[N + 1]{}, inv[N + 1]{};
  fiTable() {
    fact[0] = mint<ll, mod>(1);
    for (int i = 1; i <= N; i++) {
      fact[i] = fact[i - 1] * mint<ll, mod>(i);
    }
    inv[N] = 1 / fact[N];
    for (int i = N - 1; i >= 0; --i) {
      inv[i] = inv[i + 1] * mint<ll, mod>(i + 1);
    }
  }
  constexpr mint<ll, mod> nCk(int n, int k) {
    if (n < 0 || n < k) return mint<ll, mod>(0);
    return fact[n] * inv[k] * inv[n - k];
  }
  constexpr mint<ll, mod> nCk(mint<ll, mod> n, mint<ll, mod> k) {
    if (n.val < 0 || n.val < k.val) return mint<ll, mod>(0);
    return fact[n.val] * inv[k.val] * inv[n.val - k.val];
  }
  constexpr mint<ll, mod> nPk(int n, int k) {
    if (n < 0 || n < k) return mint<ll, mod>(0);
    return fact[n] * inv[n - k];
  }
  constexpr mint<ll, mod> nPk(mint<ll, mod> n, mint<ll, mod> k) {
    if (n.val < 0 || n.val < k.val) return mint<ll, mod>(0);
    return fact[n.val] * inv[n.val - k.val];
  }
  constexpr mint<ll, mod> operator[](int index) { return fact[index]; }
};

template <int N, ll P, ll mod>
struct pTable {
  mint<ll, mod> p[N + 1]{};
  constexpr pTable() {
    p[0] = mint<ll, mod>(1);
    for (int i = 1; i <= N; i++) p[i] = p[i - 1] * P;
  }
  constexpr mint<ll, mod> operator[](int index) { return p[index]; }
};

template <int row, int col, typename T>
struct Matrix {
  array<array<T, col>, row> arr{};
  Matrix() = default;

  explicit Matrix(const T &v) {
    for (auto &i : arr)
      for (auto &j : i) j = v;
  }
  void setId() {
    *this = Matrix();
    for (int i = 0; i < min(row, col); i++) arr[i][i] = 1;
  }

  std::array<T, col> &operator[](int id) { return arr[id]; }

  const std::array<T, col> &operator[](int id) const { return arr[id]; }

  template <int c2>
  Matrix<row, c2, T> operator*(const Matrix<col, c2, T> &a) const {
    Matrix<row, c2, T> res;
    for (int i = 0; i < row; ++i) {
      for (int k = 0; k < col; ++k) {
        for (int j = 0; j < c2; ++j) {
          res[i][j] += arr[i][k] * a[k][j];
        }
      }
    }
    return res;
  }

  Matrix &operator*=(const Matrix &a) {
    static_assert(row == col);
    *this = *this * a;
    return *this;
  }

  friend Matrix operator*(const T &c, const Matrix &b) {
    Matrix res;
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < col; j++) {
        res[i][j] = c * b[i][j];
      }
    }
    return res;
  }

  Matrix operator+(const Matrix &a) const {
    Matrix res;
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < col; ++j) res[i][j] = arr[i][j] + a[i][j];
    return res;
  }

  Matrix &operator+=(const Matrix &a) {
    *this = *this + a;
    return *this;
  }

  Matrix operator-(const Matrix &a) const {
    Matrix res;
    for (int i = 0; i < row; ++i)
      for (int j = 0; j < col; ++j) res[i][j] = arr[i][j] - a[i][j];
    return res;
  }

  Matrix &operator-=(const Matrix &a) {
    *this = *this - a;
    return *this;
  }

  Matrix pow(int n) const {
    static_assert(row == col);
    Matrix res, mult(*this);
    res.setId();
    while (n) {
      if (n & 1) res *= mult;
      mult *= mult;
      n >>= 1;
    }
    return res;
  }
};
}  // namespace mmath

namespace dataStructures {
namespace segTree {
template <typename T, class Method>
class PointSeg {
  int n;
  vector<T> tree;

 public:
  PointSeg() : PointSeg(1) {}
  PointSeg(integral auto _n) : n(_n), tree(n << 1) {}
  PointSeg(const ranges::range auto &arr) : PointSeg(ranges::size(arr)) {
    for (int i = 0; i < n; i++) tree[n + i] = arr[i];
    for (int i = n - 1; i > 0; i--)
      tree[i] = Method::merge(tree[i << 1], tree[i << 1 | 1]);
  }

  void upd(int i, T val) {
    i += n;
    Method::apply(tree[i], val);
    for (i >>= 1; i > 0; i >>= 1)
      tree[i] = Method::merge(tree[i << 1], tree[i << 1 | 1]);
  }

  T get(int l, int r) {
    if (l == r) return tree[l + n];
    if (l + 1 == r) return Method::merge(tree[l + n], tree[r + n]);
    T lVal = tree[n + l++], rVal = tree[n + r--];
    for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
      if (l & 1) lVal = Method::merge(lVal, tree[l++]);
      if (r & 1) rVal = Method::merge(tree[--r], rVal);
    }
    return Method::merge(lVal, rVal);
  }

  T getRoot() { return tree[1]; }
};

template <typename Node, typename Update, class method>
class LazySeg {
  int n;
  vector<Node> tree;
  vector<Update> lazy;
  vector<char> isLazy;

  void build(int c, int l, int r, const auto &arr) {
    if (l == r) {
      tree[c] = arr[l];
      return;
    }
    int mid = l + ((r - l) >> 1);
    build(c << 1, l, mid, arr);
    build(c << 1 | 1, mid + 1, r, arr);
    tree[c] = method::merge(tree[c << 1], tree[c << 1 | 1]);
  }

  void apply(int c, int l, int r, const Update &upd) {
    method::apply(tree[c], l, r, upd);
    if (l != r) {
      method::combine(lazy[c], upd);
      isLazy[c] = true;
    }
  }

  void push(int c, int l, int r) {
    if (isLazy[c]) {
      int mid = l + ((r - l) >> 1);
      apply(c << 1, l, mid, lazy[c]);
      apply(c << 1 | 1, mid + 1, r, lazy[c]);
      lazy[c] = Update();
      isLazy[c] = false;
    }
  }

  void update(int c, int l, int r, int x, int y, const Update &upd) {
    if (x > r || y < l) return;
    if constexpr (requires { method::break_condition(tree[c], l, r, upd); }) {
      if (method::break_condition(tree[c], l, r, upd)) return;
    }
    if (x <= l && r <= y) {
      bool tag = true;
      if constexpr (requires { method::tag_condition(tree[c], l, r, upd); })
        tag = method::tag_condition(tree[c], l, r, upd);
      if (tag) return apply(c, l, r, upd);
    }
    push(c, l, r);
    int mid = l + ((r - l) >> 1);
    update(c << 1, l, mid, x, y, upd);
    update(c << 1 | 1, mid + 1, r, x, y, upd);
    tree[c] = method::merge(tree[c << 1], tree[c << 1 | 1]);
  }

  Node query(int c, int l, int r, int x, int y) {
    if (x > r || y < l) return Node();
    if (x <= l && r <= y) {
      return tree[c];
    }
    push(c, l, r);
    int mid = l + ((r - l) >> 1);
    if (y <= mid) return query(c << 1, l, mid, x, y);
    if (x > mid) return query(c << 1 | 1, mid + 1, r, x, y);
    return method::merge(query(c << 1, l, mid, x, y),
                         query(c << 1 | 1, mid + 1, r, x, y));
  }

 public:
  LazySeg() : LazySeg(1) {};
  LazySeg(integral auto _n) : n(_n) {
    int sz = 1;
    while (sz < n) sz <<= 1;
    tree.resize(sz << 1);
    lazy.resize(sz << 1);
    isLazy.assign(sz << 1 | 1, false);
  }

  LazySeg(const ranges::range auto &arr) : LazySeg(ranges::size(arr)) {
    if (n > 0) build(1, 0, n - 1, arr);
  }

  void upd(int l, int r, const Update &upd) {
    if (l <= r && l >= 0 && r < n) {
      update(1, 0, n - 1, l, r, upd);
    }
  }

  Node get(int l, int r) {
    if (l <= r && l >= 0 && r < n) {
      return query(1, 0, n - 1, l, r);
    }
    return Node();
  }
};

struct RangeSumAdd {
  static auto merge(const auto &left, const auto &right) {
    return left + right;
  }
  static void apply(auto &node, int l, int r, const auto &upd) {
    node += upd * (r - l + 1);
  }
  static void apply(auto &node, const auto &val) { node += val; }
  static void combine(auto &current_lazy, const auto &new_upd) {
    current_lazy += new_upd;
  }
};

struct RangeSumSet {
  static auto merge(const auto &left, const auto &right) {
    return left + right;
  }
  static void apply(auto &node, int l, int r, const auto &upd) {
    node = upd * (r - l + 1);
  }
  static void apply(auto &node, const auto &val) { node = val; }
  static void combine(auto &current_lazy, const auto &new_upd) {
    current_lazy = new_upd;
  }
};

template <auto T>
struct RangeMMSet {
  static auto merge(const auto &left, const auto &right) {
    return T(left, right);
  }
  static void apply(auto &node, int l, int r, const auto &upd) { node = upd; }
  static void apply(auto &node, const auto &val) { node = val; }
  static void combine(auto &current_lazy, const auto &new_upd) {
    current_lazy = new_upd;
  }
};

template <auto T>
struct RangeMMAdd {
  static auto merge(const auto &left, const auto &right) {
    return T(left, right);
  }
  static void apply(auto &node, int l, int r, const auto &upd) { node += upd; }
  static void apply(auto &node, const auto &val) { node += val; }
  static void combine(auto &current_lazy, const auto &new_upd) {
    current_lazy += new_upd;
  }
};

struct MatrixUpdate {
  static auto merge(const auto &left, const auto &right) {
    return left + right;
  }
  static void apply(auto &node, int l, int r, const auto &upd) {
    node = upd * node;
  }
  static void apply(auto &node, const auto &val) { node = val * node; }
  static void combine(auto &current_lazy, const auto &new_upd) {
    current_lazy = new_upd * current_lazy;
  }
};

template <typename U>
using lazyTreeSumAdd = LazySeg<U, U, RangeSumAdd>;
template <typename U>
using pointTreeSumAdd = PointSeg<U, RangeSumAdd>;

template <typename U>
using lazyTreeSumSet = LazySeg<U, U, RangeSumSet>;
template <typename U>
using pointTreeSumSet = PointSeg<U, RangeSumSet>;

template <typename U>
using lazyTreeRangeMaxAdd = LazySeg<U, U, RangeMMAdd<rmax>>;
template <typename U>
using pointTreeRangeMaxAdd = PointSeg<U, RangeMMAdd<rmax>>;

template <typename U>
using lazyTreeRangeMinAdd = LazySeg<U, U, RangeMMAdd<rmin>>;
template <typename U>
using pointTreeRangeMinAdd = PointSeg<U, RangeMMAdd<rmin>>;

template <typename U>
using lazyTreeRangeMaxSet = LazySeg<U, U, RangeMMSet<rmax>>;
template <typename U>
using pointTreeRangeMaxSet = PointSeg<U, RangeMMSet<rmax>>;

template <typename U>
using lazyTreeRangeMinSet = LazySeg<U, U, RangeMMSet<rmin>>;
template <typename U>
using pointTreeRangeMinSet = PointSeg<U, RangeMMSet<rmin>>;

template <typename U, typename T>
using lazyTreeMatrixMult = LazySeg<U, T, MatrixUpdate>;
template <typename U>
using pointTreeMatrixMult = PointSeg<U, MatrixUpdate>;

/*
LAZY SEGMENT TREE

struct Update {
    1. Variablee
};

struct Node {
    1. Variables
};
*/
}  // namespace segTree
namespace bit {
template <typename T, T id, auto Merge, auto Diff>
class bit {
  int n;
  vector<T> tree;

 public:
  bit(integral auto _n) : n(_n + 10), tree(_n + 11, id) {}
  bit(const ranges::range auto &arr) : bit(arr.size()) {
    for (int i = 1; i <= arr.size(); i++) {
      tree[i] = Merge(tree[i], arr[i - 1]);
      int par = i + (i & -i);
      if (par <= n) tree[par] = Merge(tree[par], tree[i]);
    }
  }
  void upd(int i, T val) {
    for (++i; i <= n; i += i & -i) tree[i] = Merge(tree[i], val);
  }
  T get(int i) {
    T res = id;
    for (++i; i > 0; i -= i & -i) res = Merge(tree[i], res);
    return res;
  }
  T get(int l, int r) { return Diff(get(r), get(l - 1)); }
};

template <typename T, int n, T id, auto Merge, auto Diff>
class bitFX {
  T tree[n];

 public:
  bitFX() = default;
  void upd(int i, T val) {
    for (++i; i <= n; i += i & -i) tree[i] = Merge(tree[i], val);
  }
  T get(int i) {
    T res = id;
    for (++i; i > 0; i -= i & -i) res = Merge(tree[i], res);
    return res;
  }
  T get(int l, int r) { return Diff(get(r), get(l - 1)); }
};

template <typename T, T id, auto Merge, auto Diff>
class bit2D {
  int n, m;
  vector<vector<T>> tree;

 public:
  bit2D(integral auto _n)
      : n(_n + 10), m(_n + 10), tree(_n + 11, vector<T>(_n + 11, id)) {}
  bit2D(integral auto _n, integral auto _m)
      : n(_n + 10), m(_m + 10), tree(_n + 11, vector<T>(_m + 11, id)) {}
  bit2D(const auto &arr) : bit2D(arr.size(), arr[0].size()) {
    int r = arr.size(), c = arr[0].size();
    for (int i = 1; i <= r; i++) {
      for (int j = 1; j <= c; j++) {
        tree[i][j] = Merge(tree[i][j], arr[i - 1][j - 1]);
        int par = j + (j & -j);
        if (par <= m) tree[i][par] = Merge(tree[i][par], tree[i][j]);
      }
    }
    for (int j = 1; j <= c; j++) {
      for (int i = 1; i <= r; i++) {
        int par_i = i + (i & -i);
        if (par_i <= n) tree[par_i][j] = Merge(tree[par_i][j], tree[i][j]);
      }
    }
  }
  void upd(int r, int c, T val) {
    for (int i = r + 1; i <= n; i += i & -i)
      for (int j = c + 1; j <= m; j += j & -j)
        tree[i][j] = Merge(tree[i][j], val);
  }

  T get(int r, int c) {
    T res = id;
    for (int i = r + 1; i > 0; i -= i & -i)
      for (int j = c + 1; j > 0; j -= j & -j) res = Merge(tree[i][j], res);
    return res;
  }

  T get(int r1, int c1, int r2, int c2) {
    T tot = get(r2, c2);
    T s1 = get(r1 - 1, c2);
    T s2 = get(r2, c1 - 1);
    T a1 = get(r1 - 1, c1 - 1);
    return Diff(Merge(tot, a1), Merge(s1, s2));
  }
};

constexpr auto su = [](const auto &l, const auto &r) { return l + r; };
constexpr auto dif = [](const auto &l, const auto &r) { return l - r; };
constexpr auto prd = [](const auto &l, const auto &r) { return l * r; };
constexpr auto quo = [](const auto &l, const auto &r) { return l / r; };
template <typename T, T id>
using bitSum = bit<T, id, su, dif>;
template <typename T, T id, int MAXN>
using bitFxSum = bitFX<T, MAXN, id, su, dif>;
template <typename T, T id>
using bit2Dsum = bit2D<T, id, su, dif>;
template <ll m>
using bitProd = bit<mmath::mint<ll, m>, mmath::mint<ll, m>(1), prd, quo>;
template <ll m>
using bit2DProd = bit2D<mmath::mint<ll, m>, mmath::mint<ll, m>(1), prd, quo>;
}  // namespace bit
namespace bst {}
}  // namespace dataStructures

namespace Graph {
template <int sz, typename T>
void readGraph(vector<T> &graph, int n, int m) {
  graph = vector<T>(n);
  for (int i = 0; i < m; i++) {
    if constexpr (sz == 2) {
      ll u, v;
      scan(u, v);
      u--;
      v--;
      graph[u].push_back(v);
      graph[v].push_back(u);
    } else if constexpr (sz == 3) {
      ll u, v, w;
      scan(u, v, w);
      u--;
      v--;
      graph[u].emplace_back(v, w);
      graph[v].emplace_back(u, w);
    } else if constexpr (sz == 4) {
      ll u, v, w, x;
      scan(u, v, w, x);
      u--;
      v--;
      graph[u].emplace_back(v, w, x);
      graph[v].emplace_back(u, w, x);
    }
  }
}

template <int sz, typename T>
void readTree(vector<T> &graph, int n) {
  readGraph<sz>(graph, n, n - 1);
}

template <typename T>
void readTreeList(vector<T> &graph, int n) {
  graph = vector<T>(n);
  for (int i = 1, j; i < n; i++) {
    scan(j);
    j--;
    graph[i].push_back(j);
    graph[j].push_back(i);
  }
}
}  // namespace Graph

namespace pp {
auto pp(long long l, long long r, auto check) {
  return ranges::partition_point(views::iota(l, r), check);
}

auto pp(const auto &vec, auto check) {
  return ranges::partition_point(vec, check);
}

auto ppl(ld l, ld r, auto check, int iter = 60) {
  for (int i = 0; i < iter; i++) {
    ld mid = midpoint(l, r);
    if (check(mid))
      l = mid;
    else
      r = mid;
  }
  return midpoint(l, r);
}
}  // namespace pp

#endif  // TEMPLATE_H

// #ifndef TEMPLATE_MISC_H
// #define TEMPLATE_MISC_H
// #ifndef ONLINE_JUDGE
// #include "template.h"
// #endif
//
// #endif
//
// #ifndef ONLINE_JUDGE
// #include "template.h"
// #include "template_misc.h"
// #endif

const int MAXN = 2e5 + 10;
const int MAXM = 1e5 + 10;

int n, m, k, pa, pb;
ll a[MAXM];
ll b[MAXM];
ll tot[MAXN];
ll s[MAXN], t[MAXN], x[MAXN], c[MAXN];
ll cont = 0;

bool check(ll ans) {
  vll alice(m, 0), bob(m, 0), both(m, 0);
  for (int i = 0; i < k; i++) {
    // mixing 1 indexing with mod is sketchy
    // wouldn't cause re tho
    int flag = 0;
    if (s[i] <= pa && pa <= s[i] + ans) flag |= 1;
    if (s[i] + ans > n) {
      if (1 <= pa && pa <= (s[i] + ans) % n) {
        flag |= 1;
      }
    }
    if (s[i] <= pb && pb <= s[i] + ans) flag |= 2;
    if (s[i] + ans > n) {
      if (1 <= pb && pb <= (s[i] + ans) % n) {
        flag |= 2;
      }
    }
    // t is 0 indexed so ok
    if (flag == 1) alice[t[i]] += x[i];
    if (flag == 2) bob[t[i]] += x[i];
    if (flag == 3) both[t[i]] += x[i];
  }
  for (int i = 0; i < m; i++) {
    ll ra = a[i] - alice[i], rb = b[i] - bob[i];
    chmax(ra, 0);
    chmax(rb, 0);
    if (ra + rb > both[i]) return true;
  }
  return false;
}

ll get(ll ans) {
  vvpll alice(m), bob(m), both(m);
  for (int i = 0; i < k; i++) {
    int flag = 0;
    if (s[i] <= pa && pa <= s[i] + ans) flag |= 1;
    if (s[i] + ans > n) {
      if (1 <= pa && pa <= (s[i] + ans) % n) {
        flag |= 1;
      }
    }
    if (s[i] <= pb && pb <= s[i] + ans) flag |= 2;
    if (s[i] + ans > n) {
      if (1 <= pb && pb <= (s[i] + ans) % n) {
        flag |= 2;
      }
    }
    if (flag == 1) alice[t[i]].emplace_back(c[i], x[i]);
    if (flag == 2) bob[t[i]].emplace_back(c[i], x[i]);
    if (flag == 3) both[t[i]].emplace_back(c[i], x[i]);
  }
  // above is ok; just repeat of check

  ll res = 0;
  for (int i = 0; i < m; i++) {
    // greedily take what is needed by alice and bob first, prioritizing what
    // only alice or only bob can take, using what both can take when necessary
    ll cur = 0;
    rsort(alice[i]);
    rsort(bob[i]);
    rsort(both[i]);
    debug(i);
    debug(alice[i]);
    debug(bob[i]);
    debug(both[i]);
    ll ra = a[i], rb = b[i];
    priority_queue<pll> pqa, pqb;
    for (auto &[u, v] : alice[i]) {
      if (v <= ra) {
        pqa.emplace(u, v);
        cur += u * v;
        ra -= v;
      } else if (ra > 0) {
        pqa.emplace(u, ra);
        cur += u * ra;
        ra = 0;
      }
      if (ra == 0) break;
    }
    debug("1", cur);
    // take least optimal "both" for "just alice" to leave better "boths" for
    // optimizing alice and bob later
    while (ra > 0) {
      if (ra >= both[i].back().second) {
        pqa.push(both[i].back());
        cur += both[i].back().first * both[i].back().second;
        ra -= both[i].back().second;
        both[i].pop_back();
      } else {
        pqa.emplace(both[i].back().first, ra);
        cur += both[i].back().first * ra;
        both[i].back().second -= ra;
        ra = 0;
      }
    }
    debug("2", cur);
    for (auto &[u, v] : bob[i]) {
      if (v <= rb) {
        pqb.emplace(u, v);
        cur += u * v;
        rb -= v;
      } else if (rb > 0) {
        pqb.emplace(u, rb);
        cur += u * rb;
        rb = 0;
      }
      if (rb == 0) break;
    }
    debug("3", cur);
    // same logic of taking least optimal for bob as alice
    while (rb > 0) {
      if (rb >= both[i].back().second) {
        pqb.push(both[i].back());
        cur += both[i].back().first * both[i].back().second;
        rb -= both[i].back().second;
        both[i].pop_back();
      } else {
        pqb.emplace(both[i].back().first, rb);
        cur += both[i].back().first * rb;
        both[i].back().second -= rb;
        rb = 0;
      }
    }

    debug(cur);
    debug(both[i]);

    debug(pqa.size(), pqb.size());

    priority_queueMin<pll> ptot(all(both[i]));

    // sometimes, using a "both" is better than using an "only alice" or "only
    // bob". replace when better
    while (!ptot.empty()) {
      auto [cost, cnt] = ptot.top();
      ptot.pop();
      debug(cost, cnt, cur, "?");
      if (!pqa.empty() and !pqb.empty()) {
        if (pqa.top().first < pqb.top().first) {
          pqa.swap(pqb);
        }
      } else if (!pqa.empty()) {
      } else if (!pqb.empty()) {
        pqa.swap(pqb);
      } else {
        break;
      }
      if (cost < pqa.top().first) {
        auto [costa, cnta] = pqa.top();
        pqa.pop();
        if (cnt >= cnta) {
          cur -= costa * cnta;
          cur += cost * cnta;
          cnt -= cnta;
          pqa.emplace(cost, cnta);
        } else {
          cur -= costa * cnt;
          cur += cost * cnt;
          cnta -= cnt;
          debug(costa, cnta);
          pqa.emplace(costa, cnta);
          pqa.emplace(cost, cnt);
          cnt = 0;
        }
      } else {
        break;
      }
      if (cnt > 0) {
        ptot.emplace(cost, cnt);
      }
    }
    debug(cur);
    res += cur;
  }
  return res;
}

void solve() {
  scan(n, m, k, pa, pb);
  scarr(span(a, m));
  scarr(span(b, m));
  for (int i = 0; i < k; i++) {
    scan(s[i], t[i], x[i], c[i]);
    t[i]--;
    tot[t[i]] += x[i];
  }
  for (int i = 0; i < m; i++) {
    if (a[i] + b[i] > tot[i]) {
      cout << "impossible" << endl;
      return;
    }
  }
  debug("ok");
  ll ans = *pp::pp(0, n, check);
  cout << ans << ' ' << get(ans) << endl;
}

constexpr bool multitest = false;
constexpr bool _cin = false;
int main() {
#ifndef ONLINE_JUDGE
  setvbuf(stdout, NULL, _IONBF, 0);
  if (fopen("data.in", "r") != NULL) {
    freopen("data.in", "r", stdin);
  }
#else
  cin.sync_with_stdio(false);
  cin.tie(nullptr);
  cout.sync_with_stdio(false);
  cin.tie(nullptr);
#endif
  int __ = 1;
  // debug("TEST");
  if constexpr (multitest) {
    scan(__);
  }
  while (__--) {
    solve();
  }
}

void scan(integral auto &x) {
  if constexpr (_cin)
    cin >> x;
  else {
    bool s = 0;
    int c;
    while ((c = getchar_unlocked()) <= ' ');
    if (c == '-') s = 1, c = getchar_unlocked();
    for (x = 0; c >= '0'; c = getchar_unlocked())
      x = (x << 3) + (x << 1) + c - '0';
    if (s) x = -x;
  }
}

void scan(string &s) {
  if constexpr (_cin)
    cin >> s;
  else {
    s.clear();
    int c;
    while ((c = getchar_unlocked()) <= ' ' && c != -1);
    for (; c > ' ' && c != -1; c = getchar_unlocked()) s += c;
  }
}

void scan(char *s) {
  if constexpr (_cin)
    return;
  else {
    int c;
    while ((c = getchar_unlocked()) <= ' ' && c != -1);
    for (; c > ' ' && c != -1; c = getchar_unlocked()) *s++ = c;
    *s = '\0';
  }
}
