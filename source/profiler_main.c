#include <stdlib.h>
#include <stdio.h>
#include "diagnostics.h"
#include "records-sorter.h"

#define PROFILER_PRINT(msg) printf("[PROFILER]: " msg "\n")

enum Args
{
    ARG_INPUT_FILE_PATH = 1,
    OPTARG_FIRST_THRESHOLD
};

#define DEFAULT_THRESHOLD (void*)50

static void profile_execution(const char *in_path, size_t *thresholds, size_t num_thresholds)
{
    FILE *input_file;
    size_t num_records;
    size_t i;

    input_file = fopen(in_path, "r");
    ASSERT(input_file, "Unable to open the input file", profile_execution);

    init_profiler__records_sorter(input_file, &num_records);

    ASSERT(!fclose(input_file), "Unable to close the input file", profile_execution);

    PROFILER_PRINT("Processing STRING fields...");
    
    #ifndef DISABLE_MERGESORT
    profile__records_sorter(FIELD_STRING, ALGORITHM_MERGESORT, num_records, NULL);
    #endif

    #ifndef DISABLE_QUICKSORT
    profile__records_sorter(FIELD_STRING, ALGORITHM_QUICKSORT, num_records, NULL);
    #endif

    #ifndef DISABLE_MERGEBININSSORT
    if (num_thresholds > 0)
    {
        for (i = 0; i < num_thresholds; i++)
            profile__records_sorter(FIELD_STRING, ALGORITHM_MERGEBININSSORT, num_records, (void*)thresholds[i]);
    }
    else
    {
        profile__records_sorter(FIELD_STRING, ALGORITHM_MERGEBININSSORT, num_records, DEFAULT_THRESHOLD);
    }
    #endif

    #ifndef DISABLE_BININSSORT
    profile__records_sorter(FIELD_STRING, ALGORITHM_BININSSORT, num_records, NULL);
    #endif

    PROFILER_PRINT("Processing INTEGER fields...");

    #ifndef DISABLE_MERGESORT
    profile__records_sorter(FIELD_INTEGER, ALGORITHM_MERGESORT, num_records, NULL);
    #endif

    #ifndef DISABLE_QUICKSORT
    profile__records_sorter(FIELD_INTEGER, ALGORITHM_QUICKSORT, num_records, NULL);
    #endif

    #ifndef DISABLE_MERGEBININSSORT
    if (num_thresholds > 0)
    {
        for (i = 0; i < num_thresholds; i++)
            profile__records_sorter(FIELD_INTEGER, ALGORITHM_MERGEBININSSORT, num_records, (void*)thresholds[i]);
    }
    else
    {
        profile__records_sorter(FIELD_INTEGER, ALGORITHM_MERGEBININSSORT, num_records, DEFAULT_THRESHOLD);
    }
    #endif

    #ifndef DISABLE_BININSSORT
    profile__records_sorter(FIELD_INTEGER, ALGORITHM_BININSSORT, num_records, NULL);
    #endif

    PROFILER_PRINT("Processing FLOAT fields...");
    
    #ifndef DISABLE_MERGESORT
    profile__records_sorter(FIELD_FLOAT, ALGORITHM_MERGESORT, num_records, NULL);
    #endif

    #ifndef DISABLE_QUICKSORT
    profile__records_sorter(FIELD_FLOAT, ALGORITHM_QUICKSORT, num_records, NULL);
    #endif

    #ifndef DISABLE_MERGEBININSSORT
    if (num_thresholds > 0)
    {
        for (i = 0; i < num_thresholds; i++)
            profile__records_sorter(FIELD_FLOAT, ALGORITHM_MERGEBININSSORT, num_records, (void*)thresholds[i]);
    }
    else
    {
        profile__records_sorter(FIELD_FLOAT, ALGORITHM_MERGEBININSSORT, num_records, DEFAULT_THRESHOLD);
    }
    #endif

    #ifndef DISABLE_BININSSORT
    profile__records_sorter(FIELD_FLOAT, ALGORITHM_BININSSORT, num_records, NULL);
    #endif

    shutdown_profiler__records_sorter();
}


int main(int argc, char *argv[])
{
    const char *in_path;
    size_t *thresholds, thresholds_count;
    size_t i;

    ASSERT(argc > ARG_INPUT_FILE_PATH, "Wrong number of arguments passed (input file path not found)", main);

    in_path = argv[ARG_INPUT_FILE_PATH];

    thresholds = NULL;
    thresholds_count = (argc - OPTARG_FIRST_THRESHOLD);

    if (thresholds_count != 0)
    {
        thresholds = (size_t *)malloc(sizeof(size_t) * thresholds_count);
        ASSERT(thresholds, "Unable to allocate memory for thresholds", main);
    }

    for (i = OPTARG_FIRST_THRESHOLD; i < OPTARG_FIRST_THRESHOLD + thresholds_count; i++)
    {
        ASSERT(sscanf(argv[i], "%zu", &thresholds[i - OPTARG_FIRST_THRESHOLD]), "Unable to parse a sorting threshold", main);
        ASSERT(thresholds[i] > 1, "A sorting threshold must be greater than one", main);
    }

    profile_execution(in_path, thresholds, thresholds_count);

    if (thresholds)
        free(thresholds);

    return EXIT_SUCCESS;
}