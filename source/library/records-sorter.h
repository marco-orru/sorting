#pragma once
#include <stdio.h>

/**
 * @brief Specifies the various field ids to be used in 'sort_records'.
 */
typedef enum FieldId
{
    FIELD_STRING = 1, // The string field.
    FIELD_INTEGER,    // The integer field.
    FIELD_FLOAT       // The float field.
} FieldId;

/**
 * @brief Specifies the various algorithms to be used in 'sort_records'.
 */
typedef enum AlgorithmId
{
    ALGORITHM_MERGESORT = 1,  // The merge sort algorithm.
    ALGORITHM_QUICKSORT,      // The quick sort algorithm.
    ALGORITHM_BININSSORT,     // The binary insertion sort algorithm
    ALGORITHM_MERGEBININSSORT // The merge binary insertion sort algorithm
} AlgorithmId;

/**
 * @brief Function sorts records in the provided file given.
 *
 * @param in_file Define the input file.
 * @param out_file Define the output file.
 * @param field_id Define the field by which the infile should be sorted.
 * @param algorithm_id Define the algorithm used to sort the input file.
 * @param param Additional parameter to pass (i.e., the threshold of merge binary insertion sort).
 */
void sort_records(FILE *in_file, FILE *out_file, FieldId field_id, AlgorithmId algorithm_id, void *param);

#ifdef _PROFILER

/**
 * @brief Initializes he profiler loading the records.
 * @param in_file The .csv file containing the records.
 */
void init_profiler__records_sorter(FILE *in_file, size_t *num_records);

/**
 * @brief Shutdowns the profiler.
 */
void shutdown_profiler__records_sorter(void);

/**
 * @brief Profile the execution of the sorting algorithm over the unsorted array.
 * @param field_id The type of fields to be sorted.
 * @param algorithm_id The algorithm to be used.
 * @param param Additional parameter to pass (i.e., the threshold of merge binary insertion sort).
 */
void profile__records_sorter(FieldId field_id, AlgorithmId algorithm_id, size_t num_records, void* param);

#endif