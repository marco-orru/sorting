#include "sorting.h"
#include "diagnostics.h"
#include <memory.h>

/**
 * Gets a pointer to the element at the specified index inside the specified array.
 */
#define GET_ELEMENT(base, index, size) ((void *)(((unsigned char *)(base)) + (index) * (size)))

/**
 * Merges two sorted arrays into one.
 */
static void merge(void *l_base, size_t l_nitems, void *r_base, size_t r_nitems, size_t size, compare_fn comparator)
{
    void *res, *src;
    size_t res_size, l_idx, r_idx, res_idx;

    res_size = (l_nitems + r_nitems) * size;
    res = malloc(res_size);
    ASSERT(res, "Unable to allocate memory for the merging array", merge);

    l_idx = r_idx = res_idx = 0;

    while (l_idx < l_nitems && r_idx < r_nitems)
    {
        if (comparator(GET_ELEMENT(l_base, l_idx, size), GET_ELEMENT(r_base, r_idx, size)) <= 0)
        {
            src = GET_ELEMENT(l_base, l_idx++, size);
        }
        else
        {
            src = GET_ELEMENT(r_base, r_idx++, size);
        }

        ASSERT(memcpy(GET_ELEMENT(res, res_idx++, size), src, size), "Unable to copy an element to the merging array", merge);
    }

    if (l_idx < l_nitems)
        ASSERT(memcpy(GET_ELEMENT(res, res_idx, size), GET_ELEMENT(l_base, l_idx, size), size * (l_nitems - l_idx)), "Unable to copy an element to the merging array", merge);

    if (r_idx < r_nitems)
        ASSERT(memcpy(GET_ELEMENT(res, res_idx, size), GET_ELEMENT(r_base, r_idx, size), size * (r_nitems - r_idx)), "Unable to copy an element to the merging array", merge);

    ASSERT(memcpy(l_base, res, res_size), "Unable to copy the merge array to the destination", merge);

    free(res);
}

/**
 * Performs the merge sort algorithm over the provided array.
 */
static void merge_sort_rec(void *base, size_t nitems, size_t size, compare_fn comparator)
{
    size_t half;
    void *half_base;

    if (nitems == 1)
        return;

    half = nitems / 2;
    half_base = GET_ELEMENT(base, half, size);

    merge_sort_rec(base, half, size, comparator);
    merge_sort_rec(half_base, nitems - half, size, comparator);

    merge(base, half, half_base, nitems - half, size, comparator);
}

void merge_sort(void *base, size_t nitems, size_t size, compare_fn comparator)
{
    ASSERT_NULL_PARAMETER(base, merge_sort);
    ASSERT_NULL_PARAMETER(comparator, merge_sort);
    ASSERT(nitems > 0, "The array must contain at least one element", merge_sort);
    ASSERT(size > 0, "The element size cannot be zero", merge_sort);

    merge_sort_rec(base, nitems, size, comparator);
}

/**
 * Swaps two elements of an array given their indexes.
 */
static inline void exchange_values(void *base, size_t size, int left_index, int right_index, void *temp)
{
    ASSERT(memcpy(temp, GET_ELEMENT(base, left_index, size), size), "Unable to copy left into temp", exchange_values);
    ASSERT(memcpy(GET_ELEMENT(base, left_index, size), GET_ELEMENT(base, right_index, size), size), "Unable to copy right into left", exchange_values);
    ASSERT(memcpy(GET_ELEMENT(base, right_index, size), temp, size), "Unable to copy temp into right", exchange_values);
}

/**
 * Performs the partition phase of the quicksort algorithm.
 */
static int partition(void *base, int low, int high, size_t size, compare_fn comparator)
{
    void *temp;
    int pivot_index = low;
    void *pivot = GET_ELEMENT(base, pivot_index, size);
    int left = low - 1;
    int right = high + 1;

    temp = malloc(size);
    ASSERT(temp, "Unable to allocate memory for temp variable", partition);

    while (left < right)
    {
        do
        {
            left++;
        } while (comparator(GET_ELEMENT(base, left, size), pivot) < 0);

        do
        {
            right--;
        } while (comparator(GET_ELEMENT(base, right, size), pivot) > 0);

        if (left < right)
            exchange_values(base, size, left, right, temp);
    }

    free(temp);
    return right;
}

/**
 * Performs the quick sort algorithm over the provided array.
 */
static void quick_sort_rec(void *base, int low, int high, size_t size, compare_fn comparator)
{
    if (low < high)
    {
        int pivot = partition(base, low, high, size, comparator);
        quick_sort_rec(base, low, pivot, size, comparator);
        quick_sort_rec(base, pivot + 1, high, size, comparator);
    }
}

void quick_sort(void *base, size_t nitems, size_t size, compare_fn comparator)
{
    ASSERT_NULL_PARAMETER(base, quick_sort);
    ASSERT_NULL_PARAMETER(comparator, quick_sort);
    ASSERT(nitems > 0, "The array must contain at least one element", quick_sort);
    ASSERT(size > 0, "The element size cannot be zero", quick_sort);

    quick_sort_rec(base, 0, (int)(nitems - 1), size, comparator);
}

/**
 * Perform binary search on a sorted array to find the correct position for an element.
 *
 * The sorted array is the sub-array with `[0, upper - 1]` bounds of the base array, which has `[0, size - 1]` bounds.
 */
static size_t binary_search(void *base, size_t size, void *elem, size_t upper, compare_fn compare)
{
    size_t half, lower;
    void *half_elem;
    int cmp_res;

    lower = 0;

    while (lower < upper)
    {
        half = (lower + upper) / 2;
        half_elem = GET_ELEMENT(base, half, size);

        cmp_res = compare(elem, half_elem);

        if (cmp_res == 0)
            return half + 1;

        if (cmp_res > 0)
            lower = half + 1;
        else
            upper = half;
    }

    return compare(elem, GET_ELEMENT(base, lower, size)) > 0
               ? lower + 1
               : lower;
}

/**
 * Shifts to the right by one position the items in range `[insert_ids, from_idx - 1]`.
 */
static void *shift_right(void *base, size_t size, size_t insert_idx, size_t from_idx)
{
    void *pivot, *pivot_dest;
    size_t shift_sz;

    pivot = GET_ELEMENT(base, insert_idx, size);
    pivot_dest = GET_ELEMENT(base, insert_idx + 1, size);

    shift_sz = (from_idx - insert_idx) * size;
    ASSERT(memcpy(pivot_dest, pivot, shift_sz), "Unable to shift memory", shift_right);

    return pivot;
}

/**
 * Performs the binary insertion sort algorithm over the provided array.
 */
static void binary_insertion_sort_it(void *base, size_t nitems, size_t size, compare_fn comparator)
{
    size_t i, new_pos;
    void *current_elem, *src_elem, *dst_elem;

    src_elem = malloc(size);

    ASSERT(src_elem, "Unable to allocate memory for the inserted element", binary_insertion_sort_it);

    for (i = 1; i < nitems; ++i)
    {
        current_elem = GET_ELEMENT(base, i, size);
        new_pos = binary_search(base, size, current_elem, i - 1, comparator);

        ASSERT(memcpy(src_elem, current_elem, size), "Unable to save a copy of the current element", binary_insertion_sort_it);
        dst_elem = shift_right(base, size, new_pos, i);
        ASSERT(memcpy(dst_elem, src_elem, size), "Unable to copy the inserted element into its destination", binary_insertion_sort_it);
    }

    free(src_elem);
}

void binary_insertion_sort(void *base, size_t nitems, size_t size, compare_fn comparator)
{
    ASSERT_NULL_PARAMETER(base, binary_insertion_sort);
    ASSERT_NULL_PARAMETER(comparator, binary_insertion_sort);
    ASSERT(nitems > 0, "The array must contain at least one element", quick_sort);
    ASSERT(size > 0, "The element size cannot be zero", quick_sort);

    binary_insertion_sort_it(base, nitems, size, comparator);
}

/**
 * Performs the binary insertion sort algorithm over the provided array.
 */
static void merge_binary_insertion_sort_rec(void *base, size_t nitems, size_t size, size_t threshold, compare_fn comparator)
{
    if (nitems == 1)
        return;

    if (nitems <= threshold)
    {
        binary_insertion_sort(base, nitems, size, comparator);
        return;
    }

    merge_sort_rec(base, nitems, size, comparator);
}

void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t threshold, compare_fn comparator)
{
    ASSERT_NULL_PARAMETER(base, merge_binary_insertion_sort);
    ASSERT_NULL_PARAMETER(comparator, merge_binary_insertion_sort);
    ASSERT(nitems > 0, "The array must contain at least one element", merge_binary_insertion_sort);
    ASSERT(size > 0, "The element size cannot be zero", merge_binary_insertion_sort);

    merge_binary_insertion_sort_rec(base, nitems, size, threshold, comparator);
}
