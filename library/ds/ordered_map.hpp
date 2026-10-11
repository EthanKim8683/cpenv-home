template <class T, class S, class Compare = std::less<T>>
using ordered_map =
    __gnu_pbds::tree<T, S, Compare, __gnu_pbds::rb_tree_tag,
                     __gnu_pbds::tree_order_statistics_node_update>;
