namespace atcoder {
namespace internal {

template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

}  // namespace internal
}  // namespace atcoder
