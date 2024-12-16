#include <stdlib.h>
#include <string.h>
#include "diagnostics.h"
#include "records-sorter.h"

/**
 * Defines constants for indexing `argv`.
 */
enum Args
{
    ARG_IN_FILE_PATH = 1,
    ARG_OUT_FILE_PATH,
    ARG_FIELD_ID,
    ARG_ALGORITHM_ID,
    OPTARG_THRESHOLD
};

/**
 * Processes the input file.
 */
static void process_file(const char *in_path, const char *out_path, FieldId field_id, AlgorithmId algorithm_id, void* param)
{
    FILE *in_file, *out_file;

    in_file = fopen(in_path, "r");
    ASSERT(in_file, "Unable to open input file", process_file);

    out_file = fopen(out_path, "w");
    ASSERT(out_file, "Unable to open output file", process_file);

    sort_records(in_file, out_file, field_id, algorithm_id, param);

    ASSERT(!fclose(out_file), "Unable to close output file", process_file);
    ASSERT(!fclose(in_file), "Unable to close input file", process_file);
}

/**
 * Tests the string representation of the field id type.
 */
#define TEST_STR_FIELD_ID(value, str) (!strcmp("FIELD_" value, str) || !strcmp(value, str))

/**
 * Tests the string representation of the algorithm id type.
 */
#define TEST_STR_ALGORITHM_ID(value, str) (!strcmp("ALGORITHM_" value, str) || !strcmp(value, str))

/**
 * Entry point.
 */
int main(int argc, char *argv[])
{
    const char *in_path;
    const char *out_path;
    FieldId field_id;
    AlgorithmId algorithm_id;
    char field_id_str[24];
    char algorithm_id_str[24];
    int threshold;

    ASSERT(argc > ARG_IN_FILE_PATH, "Wrong number of arguments (input file path not found)", main);
    ASSERT(argc > ARG_OUT_FILE_PATH, "Wrong number of arguments (output file path not found)", main);
    ASSERT(argc > ARG_FIELD_ID, "Wrong number of arguments (field id not found)", main);
    ASSERT(argc > ARG_ALGORITHM_ID, "Wrong number of arguments (algorithm id not found)", main);

    in_path = argv[ARG_IN_FILE_PATH];
    out_path = argv[ARG_OUT_FILE_PATH];
    field_id = -1;
    algorithm_id = -1;
    threshold = -1;

    if (sscanf(argv[ARG_FIELD_ID], "%d", (int *)&field_id) != 1)
    {
        if (sscanf(argv[ARG_FIELD_ID], "%s", field_id_str) == 1)
        {
            if (TEST_STR_FIELD_ID("STRING", field_id_str))
                field_id = FIELD_STRING;
            else if (TEST_STR_FIELD_ID("INTEGER", field_id_str))
                field_id = FIELD_INTEGER;
            else if (TEST_STR_FIELD_ID("FLOAT", field_id_str))
                field_id = FIELD_FLOAT;
            else
                goto ERROR_FIELD_ID;
        }
        else
        {
        ERROR_FIELD_ID:
            PRINT_ERROR("The field id has not been correctly specified", main);
        }
    }

    if (sscanf(argv[ARG_ALGORITHM_ID], "%d", (int *)&algorithm_id) != 1)
    {
        if (sscanf(argv[ARG_ALGORITHM_ID], "%s", algorithm_id_str) == 1)
        {
            if (TEST_STR_ALGORITHM_ID("MERGESORT", algorithm_id_str))
                algorithm_id = ALGORITHM_MERGESORT;
            else if (TEST_STR_ALGORITHM_ID("QUICKSORT", algorithm_id_str))
                algorithm_id = ALGORITHM_QUICKSORT;
            else if (TEST_STR_ALGORITHM_ID("BININSSORT", algorithm_id_str))
                algorithm_id = ALGORITHM_BININSSORT;
            else if (TEST_STR_ALGORITHM_ID("MERGEBININSSORT", algorithm_id_str))
                algorithm_id = ALGORITHM_MERGEBININSSORT;
            else
                goto ERROR_ALGORITHM_ID;
        }
        else
        {
        ERROR_ALGORITHM_ID:
            PRINT_ERROR("The algorithm id has not been correctly specified", main);
        }
    }

    if (algorithm_id == ALGORITHM_MERGEBININSSORT) {

        ASSERT(argc > OPTARG_THRESHOLD, "Wrong number of arguments (merge binary insertion sort threshold not found)", main);

        threshold = atoi(argv[OPTARG_THRESHOLD]);
        ASSERT(threshold > 1, "Merge binary insertion sort threshold must be greater than one", main);
    }

    process_file(in_path, out_path, field_id, algorithm_id, (void*)(size_t)threshold);

    return EXIT_SUCCESS;
}