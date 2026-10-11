// https://codeforces.com/blog/entry/11080
template <class T, class Compare = std::less<T>>
using ordered_set =
    __gnu_pbds::tree<T, __gnu_pbds::null_type, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;
