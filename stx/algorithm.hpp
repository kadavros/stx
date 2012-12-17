#ifndef STX_STD_CONTAINERS_HPP
#define STX_STD_CONTAINERS_HPP

#include <stx/algorithm/assign.hpp>
#include <stx/algorithm/construct.hpp>
#include <stx/algorithm/destroy.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Non-modifying sequence operations
/////////////////////////////////////////////////////////////////////////////

//  stx
#include <stx/algorithm/begin.hpp>
#include <stx/algorithm/end.hpp>

//  C++98
//#include <stx/algorithm/for_each.hpp>
//#include <stx/algorithm/count.hpp>
//#include <stx/algorithm/count_if.hpp>
//#include <stx/algorithm/mismatch.hpp>
//#include <stx/algorithm/equal.hpp>
//#include <stx/algorithm/find.hpp>
//#include <stx/algorithm/find_if.hpp>
//#include <stx/algorithm/find_end.hpp>
//#include <stx/algorithm/find_first_of.hpp>
//#include <stx/algorithm/adjacent_find.hpp>
//#include <stx/algorithm/search.hpp>
//#include <stx/algorithm/search_n.hpp>

//  C++11
#include <stx/algorithm/all_of.hpp>
#include <stx/algorithm/any_of.hpp>
#include <stx/algorithm/none_of.hpp>
//#include <stx/algorithm/find_if_not.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Modifying sequence operations
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/copy.hpp>
//#include <stx/algorithm/copy_backward.hpp>
//#include <stx/algorithm/fill.hpp>
//#include <stx/algorithm/fill_n.hpp>
//#include <stx/algorithm/transform.hpp>
//#include <stx/algorithm/generate.hpp>
//#include <stx/algorithm/generate_n.hpp>
//#include <stx/algorithm/remove.hpp>
//#include <stx/algorithm/remove_if.hpp>
//#include <stx/algorithm/remove_copy.hpp>
//#include <stx/algorithm/remove_copy_if.hpp>
//#include <stx/algorithm/replace.hpp>
//#include <stx/algorithm/replace_if.hpp>
//#include <stx/algorithm/replace_copy.hpp>
//#include <stx/algorithm/replace_copy_if.hpp>
//#include <stx/algorithm/swap.hpp>
//#include <stx/algorithm/swap_ranges.hpp>
//#include <stx/algorithm/iter_swap.hpp>
//#include <stx/algorithm/reverse.hpp>
//#include <stx/algorithm/reverse_copy.hpp>
//#include <stx/algorithm/rotate.hpp>
//#include <stx/algorithm/rotate_copy.hpp>
//#include <stx/algorithm/random_shuffle.hpp>
//#include <stx/algorithm/unique.hpp>
//#include <stx/algorithm/unique_copy.hpp>

//  C++11
//#include <stx/algorithm/copy_if.hpp>
//#include <stx/algorithm/copy_n.hpp>
//#include <stx/algorithm/move.hpp>
//#include <stx/algorithm/move_backward.hpp>
//#include <stx/algorithm/shuffle.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Partitioning operations
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/partition.hpp>
//#include <stx/algorithm/stable_partition.hpp>

//  C++11
//#include <stx/algorithm/is_partitioned.hpp>
//#include <stx/algorithm/partition_copy.hpp>
//#include <stx/algorithm/partition_point.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Sorting operations (on sorted ranges)
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/sort.hpp>
//#include <stx/algorithm/partial_sort.hpp>
//#include <stx/algorithm/partial_sort_copy.hpp>
//#include <stx/algorithm/stable_sort.hpp>
//#include <stx/algorithm/nth_element.hpp>

//  C++11
//#include <stx/algorithm/is_sorted.hpp>
//#include <stx/algorithm/is_sorted_until.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Binary search operations (on sorted ranges)
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/lower_bound.hpp>
//#include <stx/algorithm/upper_bound.hpp>
//#include <stx/algorithm/binary_search.hpp>
//#include <stx/algorithm/equal_range.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Set operations (on sorted ranges)
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/merge.hpp>
//#include <stx/algorithm/inplace_merge.hpp>
//#include <stx/algorithm/includes.hpp>
//#include <stx/algorithm/set_difference.hpp>
//#include <stx/algorithm/set_intersection.hpp>
//#include <stx/algorithm/set_symmetric_difference.hpp>
//#include <stx/algorithm/set_union.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Heap operations
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/is_heap.hpp>
//#include <stx/algorithm/make_heap.hpp>
//#include <stx/algorithm/push_heap.hpp>
//#include <stx/algorithm/pop_heap.hpp>
//#include <stx/algorithm/sort_heap.hpp>

//  C++11
//#include <stx/algorithm/is_heap_until.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Minimum/maximum operations
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/max.hpp>
//#include <stx/algorithm/max_element.hpp>
//#include <stx/algorithm/min.hpp>
//#include <stx/algorithm/min_element.hpp>
//#include <stx/algorithm/lexicographical_compare.hpp>
//#include <stx/algorithm/next_permutation.hpp>
//#include <stx/algorithm/prev_permutation.hpp>

//  C++11
//#include <stx/algorithm/minmax.hpp>
//#include <stx/algorithm/minmax_element.hpp>
//#include <stx/algorithm/is_permutation.hpp>

/////////////////////////////////////////////////////////////////////////////
//  Numeric operations
/////////////////////////////////////////////////////////////////////////////

//  C++98
//#include <stx/algorithm/accumulate.hpp>
//#include <stx/algorithm/inner_product.hpp>
//#include <stx/algorithm/adjacent_difference.hpp>
//#include <stx/algorithm/partial_sum.hpp>

//  C++11
//#include <stx/algorithm/iota.hpp>

#endif // STX_STD_CONTAINERS_HPP
