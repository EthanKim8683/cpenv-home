
template <class S>
S sa(S state, double T0, double T1, double tl = 1.95) {
  using namespace chrono;
  auto t0 = steady_clock::now();
  double T;
  int score = state.score(), best_score = score;
  S best_state = state;
  for (int i = 0;; i++) {
    if ((i & 255) == 0) {
      double w = duration<double>(steady_clock::now() - t0).count() / tl;
      if (w >= 1.0) break;
      T = T0 * pow(T1 / T0, w);
    }
    auto move = state.gen();
    int delta = state.eval(move);
    if (delta <= 0 || (T > 1e-9 && frng() < exp(-delta / T))) {
      state.apply(move);
      score += delta;
      if (score < best_score) {
        best_score = score;
        best_state = state;
      }
    }
  }
  return best_state;
}
