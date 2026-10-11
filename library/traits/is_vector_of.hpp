// https://stackoverflow.com/a/16337657
template <class, class>
struct is_vector_of : std::false_type {};
template <class T, class S>
struct is_vector_of<T, std::vector<T, S>> : std::true_type {};
template <class T, class S>
inline constexpr bool is_vector_of_v = is_vector_of<T, S>::value;
