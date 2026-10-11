namespace atcoder {
namespace internal {

template <class>
struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

}  // namespace internal
}  // namespace atcoder
