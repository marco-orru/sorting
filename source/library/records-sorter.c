#include "records-sorter.h"
#include "diagnostics.h"
#include "sorting.h"
#include <stdlib.h>
#include <string.h>

#ifndef STRING_FIELD_LEN
/**
 * The max length of the string field.
 * @note: Strings are stored statically to prevent allocations and memory fragmentation.
 */
#define STRING_FIELD_LEN 32
#endif

/**
 * The field id used for comparision.
 */
static int g_field_id;

/**
 * Represents a record, made of an identifier and three fields (string, integer and floating point).
 */
typedef struct Record
{
    int id;                        /** The identifier of the record. */
    char field1[STRING_FIELD_LEN]; /** The string field. */
    int field2;                    /** The integer field. */
    float field3;                  /** The floating point field. */
} Record;

/**
 * Counts the number of records inside the specified file, and its maximum line length.
 */
static size_t count_records(FILE *infile, size_t *max_line_len)
{
    int current;
    size_t count, current_line_len;

    *max_line_len = current_line_len = 0;
    count = 0;

    while ((current = fgetc(infile)) != EOF)
    {
        current_line_len++;

        if (current == '\n')
        {
            if (current_line_len > *max_line_len)
                *max_line_len = current_line_len;

            current_line_len = 0;
            count++;
        }
    }

    rewind(infile);

    return count;
}

/**
 * Parse the current line into a record.
 */
static void read_record(char *line, Record *record)
{
    char *field;

    field = strtok(line, ",");
    record->id = atoi(field);

    field = strtok(NULL, ",");
    strcpy(record->field1, field);

    field = strtok(NULL, ",");
    record->field2 = atoi(field);

    field = strtok(NULL, ",");
    record->field3 = (float)atof(field);
}

/**
 * Loads the records in the specified file to the specified array.
 */
static void load_records(FILE *in_file, size_t max_line_len, Record *records, size_t num_records)
{
    char *line;
    size_t i;

    line = malloc(sizeof(char) * (max_line_len + 1));
    ASSERT(line, "Unable to allocate space for 'line'", load_records);

    i = 0;

    while (i < num_records)
    {
        ASSERT(fgets(line, (int)(max_line_len + 1), in_file), "Unable to read line from input file", load_records);
        read_record(line, &records[i++]);
    }

    free(line);
}

/**
 * Stores the records in the specified file from the specified records array.
 */
static void store_records(FILE *out_file, Record *records, size_t num_records)
{
    size_t i;

    i = 0;

    for (i = 0; i < num_records; i++)
    {
        fprintf(out_file, "%d,%s,%d,%f\n",
                records[i].id,
                records[i].field1,
                records[i].field2,
                records[i].field3);
    }
}

/**
 * The record comparision function.
 */
static int compare_records_fn(const void *record_a, const void *record_b)
{
    const Record *a = (const Record *)record_a;
    const Record *b = (const Record *)record_b;

    switch (g_field_id)
    {
    case FIELD_STRING:
        return string_comparator(a->field1, b->field1);
    case FIELD_INTEGER:
        return int_comparator(&a->field2, &b->field2);
    case FIELD_FLOAT:
        return float_comparator(&a->field3, &b->field3);
    }

    PRINT_ERROR("Invalid field ID", compare_records_fn);
}

void sort_records(FILE *in_file, FILE *out_file, FieldId field_id, AlgorithmId algorithm_id, void *param)
{
    size_t max_line_len;
    size_t num_records;
    Record *records;

    ASSERT_NULL_PARAMETER(in_file, sort_records);
    ASSERT_NULL_PARAMETER(out_file, sort_records);
    ASSERT(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT, "Invalid field id", sort_records);
    ASSERT(algorithm_id >= ALGORITHM_MERGESORT && algorithm_id <= ALGORITHM_MERGEBININSSORT, "Invalid algorithm id", sort_records);

    printf("Analyzing input file...\n");
    num_records = count_records(in_file, &max_line_len);

    records = calloc(num_records, sizeof(Record));
    ASSERT(records, "Unable to allocate space for 'records'", sort_records);

    printf("Loading records...\n");
    load_records(in_file, max_line_len, records, num_records);

    g_field_id = field_id;

    printf("Sorting records...\n");
    switch (algorithm_id)
    {
    case ALGORITHM_MERGESORT:
        merge_sort(records, num_records, sizeof(Record), compare_records_fn);
        break;
    case ALGORITHM_QUICKSORT:
        quick_sort(records, num_records, sizeof(Record), compare_records_fn);
        break;
    case ALGORITHM_BININSSORT:
        binary_insertion_sort(records, num_records, sizeof(Record), compare_records_fn);
        break;
    case ALGORITHM_MERGEBININSSORT:
        merge_binary_insertion_sort(records, num_records, sizeof(Record), (size_t)param, compare_records_fn);
        break;
    default:
        PRINT_ERROR("Invalid sorting algorithm id", sort_records);
        break;
    }

    printf("Saving records...\n");
    store_records(out_file, records, num_records);

    free(records);
    printf("Done\n");
}

#ifdef _PROFILER

#include <time.h>

/**
 * Macro to print a profiler-specific message.
 * @param msg The message to print.
 */
#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")

/**
 * Macro to print the profiling result.
 * @param field_id The field used for sorting.
 * @param algorithm_id The algorithm used for sorting.
 * @param start The start time of the sorting.
 * @param end The end time of the sorting.
 */
#define PROFILER_PRINT_RESULT(field_id, algorithm_id, start, end) \
    printf("[PROFILER]<field=%s, algorithm=%s>: Sorted in %f seconds", get_field_name((field_id)), get_algorithm_name((algorithm_id)), (double)((end) - (start)) / CLOCKS_PER_SEC)

/**
 * Pointer to store the unsorted records used for profiling.
 */
static Record *unsorted_records = NULL;

void init_profiler__records_sorter(FILE *in_file, size_t *num_records)
{
    size_t max_line_len;

    ASSERT_NULL_PARAMETER(in_file, init_profiler__records_sorter);
    ASSERT(!unsorted_records, "Profiler has been already initialized", init_profiler__records_sorter);

    PROFILER_PRINT("Initializing profiler...");

    *num_records = count_records(in_file, &max_line_len);

    PROFILER_PRINT("Allocating unsorted records...");
    unsorted_records = (Record *)malloc(sizeof(Record) * *num_records);
    ASSERT(unsorted_records, "Unable to allocate memory for the unsorted records array", init_profiler__records_sorter);

    PROFILER_PRINT("Loading records...");
    load_records(in_file, max_line_len, unsorted_records, *num_records);

    PROFILER_PRINT("Profiler initialized.");
}

void shutdown_profiler__records_sorter(void)
{
    ASSERT(unsorted_records, "Profiler already shut down", shutdown_profiler__records_sorter);

    PROFILER_PRINT("Shutting down profiler...");

    PROFILER_PRINT("Deallocating unsorted records...");
    free((void *)unsorted_records);

    PROFILER_PRINT("Profiler shut down.");
}

/**
 * Retrieves the name of the field corresponding to the specified FieldId.
 *
 * @param field_id The ID of the field.
 * @return A string representing the name of the field.
 */
static const char *get_field_name(FieldId field_id)
{
    switch (field_id)
    {
    case FIELD_STRING:
        return "STRING";
    case FIELD_INTEGER:
        return "INTEGER";
    case FIELD_FLOAT:
        return "FLOAT";
    }

    PRINT_ERROR("Invalid field ID", get_field_name);
}

/**
 * Retrieves the name of the sorting algorithm corresponding to the specified AlgorithmId.
 *
 * @param algorithm_id The ID of the sorting algorithm.
 * @return A string representing the name of the algorithm.
 */
static const char *get_algorithm_name(AlgorithmId algorithm_id)
{
    switch (algorithm_id)
    {
    case ALGORITHM_MERGESORT:
        return "MERGESORT";
    case ALGORITHM_QUICKSORT:
        return "QUICKSORT";
    case ALGORITHM_BININSSORT:
        return "BINARYINSERTIONSORT";
    case ALGORITHM_MERGEBININSSORT:
        return "MERGEBINARYINSERTIONSORT";
    }

    PRINT_ERROR("Invalid algorithm ID", get_algorithm_name);
}

void profile__records_sorter(FieldId field_id, AlgorithmId algorithm_id, size_t num_records, void *param)
{
    Record *to_be_sorted;
    clock_t start, end;

    ASSERT(field_id >= FIELD_STRING && field_id <= FIELD_FLOAT, "The field id is not in the valid range [1, 3]", profile__records_sorter);
    ASSERT(algorithm_id >= ALGORITHM_MERGESORT && algorithm_id <= ALGORITHM_MERGEBININSSORT, "The algorithm id is not in the valid range [1, 2]", profile__records_sorter);

    to_be_sorted = (Record *)malloc(sizeof(Record) * num_records);
    ASSERT(to_be_sorted, "Unable to allocate memory for records to be sorted", profile__records_sorter);

    ASSERT(memcpy(to_be_sorted, unsorted_records, sizeof(Record) * num_records), "Unable to copy the unsorted records array", profile__records_sorter);

    g_field_id = field_id;

    switch (algorithm_id)
    {
    case ALGORITHM_MERGESORT:
        start = clock();
        merge_sort(to_be_sorted, num_records, sizeof(Record), compare_records_fn);
        end = clock();
        break;
    case ALGORITHM_QUICKSORT:
        start = clock();
        quick_sort(to_be_sorted, num_records, sizeof(Record), compare_records_fn);
        end = clock();
        break;
    case ALGORITHM_BININSSORT:
        start = clock();
        binary_insertion_sort(to_be_sorted, num_records, sizeof(Record), compare_records_fn);
        end = clock();
        break;
    case ALGORITHM_MERGEBININSSORT:
        start = clock();
        merge_binary_insertion_sort(to_be_sorted, num_records, sizeof(Record), (size_t)param, compare_records_fn);
        end = clock();
        break;
    default:
        UNREACHABLE();
        break;
    }

    PROFILER_PRINT_RESULT(field_id, algorithm_id, start, end);

    if (algorithm_id == ALGORITHM_MERGEBININSSORT)
        printf("(Threshold used: %zu)", (size_t)param);

    printf(".\n");

    free((void *)to_be_sorted);

    g_field_id = -1;
}

#endif