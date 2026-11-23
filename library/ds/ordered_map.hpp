#include <bits/extc++.h>

using namespace __gnu_pbds;

template <class S, class T, class U = less<T>>
using ordered_map =
    tree<S, T, U, rb_tree_tag, tree_order_statistics_node_update>;
