template <class T>
struct is_invertible : std::is_floating_point<T> {};
template <int MOD>
struct is_invertible<atcoder::static_modint<MOD>> : std::true_type {};
template <int ID>
struct is_invertible<atcoder::dynamic_modint<ID>> : std::true_type {};
template <class T>
inline constexpr bool is_invertible_v = is_invertible<T>::value;
