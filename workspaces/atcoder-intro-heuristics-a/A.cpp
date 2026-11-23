#ifndef U
#pragma GCC optimize("Ofast,unroll-loops")
#endif
#include <bits/stdc++.h>

using namespace std;

#define int long long
// #define double long double
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

int chmin(auto &u, auto v) { return u > v ? u = v, 1 : 0; }
int chmax(auto &u, auto v) { return u < v ? u = v, 1 : 0; }

inline uint64_t rng() {
  static uint64_t x = 88172645463325252ULL;
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  return x * 0x2545F4914F6CDD1DULL;
}

inline uint32_t rng(uint32_t n) { return ((rng() >> 32) * n) >> 32; }

inline double frng() { return (rng() >> 11) * (1. / (1ll << 53)); }

template <class S>
S sa(S state, double T0, double T1, double tl = 1.95) {
  using namespace chrono;
  auto t0 = steady_clock::now();
  double T;
  int score = state.score(), best_score = score;
  S best_state = state;
  // double avg_prob = 0;
  for (int i = 0;; i++) {
    if ((i & 255) == 0) {
      double w = duration<double>(steady_clock::now() - t0).count() / tl;
      if (w >= 1.0) break;
      T = T0 * pow(T1 / T0, w);
    }
    auto move = state.gen();
    int delta = state.eval(move);
    // if (delta > 0) {
    //   double prob = clamp(exp(-delta / T), 0., 1.);
    //   if (avg_prob == 0) {
    //     avg_prob = prob;
    //   } else {
    //     double alpha = 1 - 1e-3;
    //     avg_prob = alpha * avg_prob + (1 - alpha) * prob;
    //   }
    // }
    if (delta <= 0 || (T > 1e-9 && frng() < exp(-delta / T))) {
      state.apply(move);
      score += delta;
      if (score < best_score) {
        best_score = score;
        best_state = state;
      }
    }
    // if ((i - 10) % 100000 == 0) {
    //   cerr << avg_prob << '\n';
    // }
  }
  cerr << best_score << '\n';
  return best_state;
}

int D, C[26], S[365][26];

struct State {
  int t[365], base_score = 0;
  set<int> indices[26];
  State() {
    rep(i, 0, 26) { indices[i].insert(-1); }
    rep(i, 0, D) {
      t[i] = rng(26);
      indices[t[i]].insert(i);
    }
    rep(i, 0, 26) { indices[i].insert(D); }

    rep(i, 0, D) { base_score += S[i][t[i]]; }
    rep(i, 0, 26) {
      for (auto it = indices[i].begin(); next(it) != indices[i].end(); it++) {
        int d = *next(it) - *it - 1;
        base_score -= C[i] * d * (d + 1) / 2;
      }
    }
  }
  int score() { return -base_score; }
  pii gen() { return {rng(D), rng(26)}; }
  int eval(pii move) {
    auto [i, x] = move;
    if (x == t[i]) return 0;
    int rv = 0;
    rv -= S[i][t[i]];
    rv += S[i][x];
    {
      int c = C[t[i]];
      auto it = indices[t[i]].find(i);
      {
        int d = *it - *prev(it) - 1;
        rv += c * d * (d + 1) / 2;
      }
      {
        int d = *next(it) - *it - 1;
        rv += c * d * (d + 1) / 2;
      }
      {
        int d = *next(it) - *prev(it) - 1;
        rv -= c * d * (d + 1) / 2;
      }
    }
    {
      int c = C[x];
      auto it = indices[x].upper_bound(i);
      {
        int d = *it - *prev(it) - 1;
        rv += c * d * (d + 1) / 2;
      }
      {
        int d = *it - i - 1;
        rv -= c * d * (d + 1) / 2;
      }
      {
        int d = i - *prev(it) - 1;
        rv -= c * d * (d + 1) / 2;
      }
    }
    return -rv;
  }
  void apply(pii move) {
    auto [i, x] = move;
    indices[t[i]].erase(i);
    t[i] = x;
    indices[x].insert(i);
  }
};

signed main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  cin >> D;

  for (auto &e : C) cin >> e;

  rep(i, 0, D) {
    for (auto &e : S[i]) {
      cin >> e;
    }
  }

  State best_state = sa<State>(State(), 1.9e4 / log(2.l), 1e4 / log(100.l));
  rep(i, 0, D) { cout << best_state.t[i] + 1 << '\n'; }
}
