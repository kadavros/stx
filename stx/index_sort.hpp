#ifndef STX_INDEX_SORT_HPP
#define STX_INDEX_SORT_HPP

/*
    index_sort - fast O(N) _integer_ sorting algorithm which uses additional
    memory for sorting. Amount of needed memory depends basically on the range
    of numbers in input array. Typically this algorithm allocates about
    (max_value - min_value + 1)*sizeof(uint32_t) bytes. So it could be
    impractical to use index_sort for input arrays which contain values
    from 0 to UINT32_MAX, because it will require about 16 Gb of memory.
    If index_sort fails to allocated required memory, it returns false and
    input array remains unsorted.
    
    Considering the remark above, typical index_sort usage looks like this:
        std::vector<int> v;
        // v gets initialized here
        if (!stx::index_sort(v)) std::sort(v.begin(), v.end());
    
    This is _not_ general purpose sorting algorithm, but rather an optimized
    version for several kinds of input data (array of integers with relatively
    narrow range of it's values).
*/

#include <stddef.h> // size_t
#include <limits.h> // UCHAR_MAX, USHRT_MAX, UINT_MAX, ULONG_MAX
#include <iterator> // advance(), distance(), iterator_traits
#include <vector>   // vector
#include <new>      // bad_alloc
#include <stx/int_types/long_long.hpp>

#ifndef SIZE_T_MAX
#   define SIZE_T_MAX ((size_t) -1)
#endif

namespace stx {

template <class ForwardIterator, class Integer, class TmpArrayType>
inline bool index_sort_impl(
    ForwardIterator first,
    size_t size,
    Integer min_value,
    Integer max_value)
{
    if (size <= 1) {
        return true;
    }
    
    //  Suppose "Integer" is "unsigned long", max_value == ULONG_MAX,
    //  min_value == 0, and size_t also has underlying type "unsigned long".
    //  Then tmp_array_size will equal ULONG_MAX + 1, which can't
    //  be represented with "unsigned long" type. In this case we must
    //  handle this situation somehow, for example: count how much values
    //  equal ULONG_MAX, store this value as num_size_t_max_values, then
    //  assign those values ULONG_MAX - 1, and after sorting is
    //  complete assign last num_size_t_max_values values ULONG_MAX.
    size_t tmp_array_size;
    bool special_case = false;
    size_t num_size_t_max_values = 0;
    
    if (max_value > 0 && (size_t) max_value == SIZE_T_MAX && min_value == 0) {
        //  Special case, described above.
        tmp_array_size = max_value;
        special_case = true;
    } else {
        tmp_array_size = max_value - min_value + 1;
    }
    
    if (tmp_array_size > SIZE_T_MAX/sizeof(TmpArrayType)) {
        //  Can't allocate memory: size_t overflow.
        return false;
    }
    
    ForwardIterator i;
	size_t n;
	TmpArrayType x, k;
    
    if (special_case) {
        i = first;
        for (n = 0; n < size; ++n, ++i) {
            if ((size_t) *i == SIZE_T_MAX) {
                ++num_size_t_max_values;
                --(*i);
            }
        }
    }
    
    std::vector<TmpArrayType> tmp_array;
    try {
        tmp_array.resize(tmp_array_size, 0);
    } catch (std::bad_alloc&) {
        return false;
    }
    
    i = first;
    n = 0;
    for (; n < size; ++n, ++i) {
        ++tmp_array[*i - min_value];
    }
    
    i = first;
    n = 0;
    for (; n < tmp_array_size ; ++n) {
        x = tmp_array[n];
        if (x) {
            for (k = 0; k < x; ++k) {
                *i = n + min_value;
                ++i;
            }
        }
    }
    
    if (special_case) {
        i = first;
        n = size - num_size_t_max_values;
        std::advance(i, n);
        for (; n < size; ++n) {
            *i = SIZE_T_MAX;
        }
    }
    
    return true;
}

template <class ForwardIterator, class Integer>
inline bool index_sort(
    ForwardIterator first,
    size_t size,
    Integer min_value,
    Integer max_value)
{
    bool ret = true;
    if (size <= 1) {
        return ret;
    }
    
    if (size <= UCHAR_MAX) {
        ret = index_sort_impl<ForwardIterator, Integer, unsigned char>(first, size, min_value, max_value);
    } else if (size <= USHRT_MAX) {
        ret = index_sort_impl<ForwardIterator, Integer, unsigned short>(first, size, min_value, max_value);
    } else if (size <= UINT_MAX) {
        ret = index_sort_impl<ForwardIterator, Integer, unsigned int>(first, size, min_value, max_value);
    } else if (size <= ULONG_MAX) {
        ret = index_sort_impl<ForwardIterator, Integer, unsigned long>(first, size, min_value, max_value);
    }
#   if STX_HAS_LONG_LONG
    else {
        ret = index_sort_impl<ForwardIterator, Integer, unsigned long long>(first, size, min_value, max_value);
    }
#   else
    else {
        ret = false;
    }
#   endif
    
    return ret;
}

template <class ForwardIterator, class Integer>
inline bool index_sort(
    ForwardIterator first,
    ForwardIterator last,
    Integer min_value,
    Integer max_value)
{
    size_t size = std::distance(first, last);
    return index_sort(first, size, min_value, max_value);
}

template <class ForwardIterator>
inline bool index_sort(ForwardIterator first, size_t size)
{
    if (size <= 1) {
        return true;
    }
    typedef typename std::iterator_traits<ForwardIterator>::value_type value_type;
    value_type min_value = *first; //std::numeric_limits<value_type>::max();
    value_type max_value = *first; //std::numeric_limits<value_type>::min();
    ForwardIterator i = first;
    ++i;
    size_t n = 1;
    for (; n < size; ++n, ++i) {
        if (*i < min_value) {
            min_value = *i;
        }
        if (*i > max_value) {
            max_value = *i;
        }
    }
    return index_sort(first, size, min_value, max_value);
}

template <class ForwardIterator>
inline bool index_sort(ForwardIterator first, ForwardIterator last)
{
    size_t size = std::distance(first, last);
    return index_sort(first, size);
}

} // namespace stx

#endif // STX_INDEX_SORT_HPP
