#include <bits/extc++.h>

using namespace __gnu_pbds;

template <class S, class T = less<S>>
using ordered_set =
    tree<S, null_type, T, rb_tree_tag, tree_order_statistics_node_update>;
