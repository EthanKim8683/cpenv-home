// https://stackoverflow.com/a/16337657
template <class>
struct is_vector : std::false_type {};
template <class T, class S>
struct is_vector<std::vector<T, S>> : std::true_type {};
template <class T>
inline constexpr bool is_vector_v = is_vector<T>::value;
