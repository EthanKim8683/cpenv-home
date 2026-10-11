template <class T>
struct combinatorics_cache {
  inline static std::vector<T> fact = {1};
  inline static std::vector<T> inv_fact = {1};

  static void reset() {
    fact = {1};
    inv_fact = {1};
  }
};
