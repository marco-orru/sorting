#pragma once

#include <stdio.h>
#include "comparators.h"

/**
 * @brief Sorts the provided array with the merge sort algorithm.
 *
 * @param base       Pointer to the beginning of the array to be sorted.
 * @param nitems     Number of elements in the array.
 * @param size       Size of each element in the array, in bytes.
 * @param comparator Pointer to the comparison function that defines the order of elements.
 *
 * @note This operation has linearithmic time complexity O(N log N).
 */
void merge_sort(void *base, size_t nitems, size_t size, compare_fn comparator);

/**
 * @brief Sorts the provided array with the quick sort algorithm.
 *
 * @param base       Pointer to the beginning of the array to be sorted.
 * @param nitems     Number of elements in the array.
 * @param size       Size of each element in the array, in bytes.
 * @param comparator Pointer to the comparison function that defines the order of elements.
 *
 * @note This operation has linearithmic time complexity O(N log N).
 */
void quick_sort(void *base, size_t nitems, size_t size, compare_fn comparator);

/**
 * @brief Sorts the provided array with the binary insertion sort algorithm.
 *
 * @param base       Pointer to the beginning of the array to be sorted.
 * @param nitems     Number of elements in the array.
 * @param size       Size of each element in the array, in bytes.
 * @param comparator Pointer to the comparison function that defines the order of elements.
 *
 * @note This operation has linearithmic time complexity O(N log N).
 */
void binary_insertion_sort(void *base, size_t nitems, size_t size, compare_fn compare);

/**
 * @brief Perform a hybrid sorting algorithm that combines binary insertion sort and merge sort over an array of
 * generic items.
 *
 * @remark This function recursively applies merge sort until the array size falls below a specified threshold,
 * at which point it switches to binary insertion sort for smaller partitions.
 *
 * @param base       Pointer to the beginning of the array to be sorted.
 * @param nitems      Number of elements in the array.
 * @param size       Size of each element in the array, in bytes.
 * @param threshold  The threshold at which the algorithm switches from merge sort to binary insertion sort.
 * @param comparator Pointer to the comparison function that defines the order of elements.
 *
 * @note This operation has linearithmic time complexity O(N log N).
 */
void merge_binary_insertion_sort(void *base, size_t nitems, size_t size, size_t threshold, compare_fn comparator);
