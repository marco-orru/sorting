#include <time.h>
#include <stdlib.h>
#include "unity.h"
#include "sorting.h"

/*---------------------------------------------------------------------------------------------------------------*/

// PURPOSE: Gets a pointer to the element at the specified index inside the specified array.
#define GET_ELEMENT(base, index, size) ((void *)(((unsigned char *)(base)) + (index) * (size)))

// PURPOSE: Returns 1 if the array is sorted, 0 otherwise.
static int is_array_sorted(const void *arr, size_t count, size_t size, compare_fn comparator)
{
    size_t i;

    for (i = 1; i < count; i++)
    {
        if (comparator(GET_ELEMENT(arr, i - 1, size), GET_ELEMENT(arr, i, size)) > 0)
            return 0;
    }

    return 1;
}

/*---------------------------------------------------------------------------------------------------------------*/

#define RANDOM_INT_MIN 0
#define RANDOM_INT_MAX 10000

// PURPOSE: Generates a random integer between RANDOM_INT_MIN and RANDOM_INT_MAX.
static int rand_int(void)
{
    return rand() % (RANDOM_INT_MAX - RANDOM_INT_MIN + 1) + RANDOM_INT_MIN;
}

// PURPOSE: Generates a random thresold (a multiple of 5 between 5 and 50000).
static size_t rand_threshold(void)
{
    return (size_t)(rand() % (9999) + 1) * 5;
}

#define RANDOM_FLOAT_MIN 0.f
#define RANDOM_FLOAT_MAX 10000.f

// PURPOSE: Generates a random integer between RANDOM_INT_MIN and RANDOM_FLOAT_MAX.
static float rand_float(void)
{
    return ((float)rand() / RAND_MAX) * (RANDOM_FLOAT_MAX - RANDOM_FLOAT_MIN) + RANDOM_FLOAT_MIN;
}

#define RANDOM_STRING_MIN 5
#define RANDOM_STRING_MAX 20

// PURPOSE: Generates a random string of a random lenght between RANDOM_STRING_MIN and RANDOM_STRING_MAX.
static char *rand_string(void)
{
    size_t length, i;
    char *str;

    length = rand() % (RANDOM_STRING_MAX - RANDOM_STRING_MIN + 1) + RANDOM_STRING_MIN;
    str = malloc(sizeof(char) * length);

    for (i = 0; i < length - 1; i++)
        str[i] = (char)(rand() % (UCHAR_MAX + 1));

    str[i] = '\0';
    return str;
}

/*---------------------------------------------------------------------------------------------------------------*/

static void merge_sort_int_array_test(int size)
{
    int *array;
    size_t i;

    array = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_int();

    merge_sort(array, size, sizeof(int), int_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(int), int_comparator));

    free(array);
}

static void merge_sort_test_int_array_10(void)
{
    merge_sort_int_array_test(10);
}

static void merge_sort_test_int_array_100(void)
{
    merge_sort_int_array_test(100);
}

static void merge_sort_test_int_array_1000(void)
{
    merge_sort_int_array_test(1000);
}

static void merge_sort_test_int_array_10000(void)
{
    merge_sort_int_array_test(10000);
}

static void merge_sort_test_int_array_100000(void)
{
    merge_sort_int_array_test(100000);
}

static void merge_sort_test_int_array_1000000(void)
{
    merge_sort_int_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void merge_sort_float_array_test(int size)
{
    float *array;
    size_t i;

    array = malloc(sizeof(float) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_float();

    merge_sort(array, size, sizeof(float), float_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(float), float_comparator));

    free(array);
}

static void merge_sort_test_float_array_10(void)
{
    merge_sort_float_array_test(10);
}

static void merge_sort_test_float_array_100(void)
{
    merge_sort_float_array_test(100);
}

static void merge_sort_test_float_array_1000(void)
{
    merge_sort_float_array_test(1000);
}

static void merge_sort_test_float_array_10000(void)
{
    merge_sort_float_array_test(10000);
}

static void merge_sort_test_float_array_100000(void)
{
    merge_sort_float_array_test(100000);
}

static void merge_sort_test_float_array_1000000(void)
{
    merge_sort_float_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void merge_sort_string_array_test(int size)
{
    char **array;
    size_t i;

    array = malloc(sizeof(char *) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_string();

    merge_sort(array, size, sizeof(char *), dyn_string_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(char *), dyn_string_comparator));

    for (i = 0; i < size; i++)
        free(array[i]);

    free(array);
}

static void merge_sort_test_string_array_10(void)
{
    merge_sort_string_array_test(10);
}

static void merge_sort_test_string_array_100(void)
{
    merge_sort_string_array_test(100);
}

static void merge_sort_test_string_array_1000(void)
{
    merge_sort_string_array_test(1000);
}

static void merge_sort_test_string_array_10000(void)
{
    merge_sort_string_array_test(10000);
}

static void merge_sort_test_string_array_100000(void)
{
    merge_sort_string_array_test(100000);
}

static void merge_sort_test_string_array_1000000(void)
{
    merge_sort_string_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void quick_sort_int_array_test(int size)
{
    int *array;
    size_t i;

    array = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_int();

    quick_sort(array, size, sizeof(int), int_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(int), int_comparator));

    free(array);
}

static void quick_sort_test_int_array_10(void)
{
    quick_sort_int_array_test(10);
}

static void quick_sort_test_int_array_100(void)
{
    quick_sort_int_array_test(100);
}

static void quick_sort_test_int_array_1000(void)
{
    quick_sort_int_array_test(1000);
}

static void quick_sort_test_int_array_10000(void)
{
    quick_sort_int_array_test(10000);
}

static void quick_sort_test_int_array_100000(void)
{
    quick_sort_int_array_test(100000);
}

static void quick_sort_test_int_array_1000000(void)
{
    quick_sort_int_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void quick_sort_float_array_test(int size)
{
    float *array;
    size_t i;

    array = malloc(sizeof(float) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_float();

    quick_sort(array, size, sizeof(float), float_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(float), float_comparator));

    free(array);
}

static void quick_sort_test_float_array_10(void)
{
    quick_sort_float_array_test(10);
}

static void quick_sort_test_float_array_100(void)
{
    quick_sort_float_array_test(100);
}

static void quick_sort_test_float_array_1000(void)
{
    quick_sort_float_array_test(1000);
}

static void quick_sort_test_float_array_10000(void)
{
    quick_sort_float_array_test(10000);
}

static void quick_sort_test_float_array_100000(void)
{
    quick_sort_float_array_test(100000);
}

static void quick_sort_test_float_array_1000000(void)
{
    quick_sort_float_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void quick_sort_string_array_test(int size)
{
    char **array;
    size_t i;

    array = malloc(sizeof(char *) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_string();

    quick_sort(array, size, sizeof(char *), dyn_string_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(char *), dyn_string_comparator));

    for (i = 0; i < size; i++)
        free(array[i]);

    free(array);
}

static void quick_sort_test_string_array_10(void)
{
    quick_sort_string_array_test(10);
}

static void quick_sort_test_string_array_100(void)
{
    quick_sort_string_array_test(100);
}

static void quick_sort_test_string_array_1000(void)
{
    quick_sort_string_array_test(1000);
}

static void quick_sort_test_string_array_10000(void)
{
    quick_sort_string_array_test(10000);
}

static void quick_sort_test_string_array_100000(void)
{
    quick_sort_string_array_test(100000);
}

static void quick_sort_test_string_array_1000000(void)
{
    quick_sort_string_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void binary_insertion_sort_int_array_test(int size)
{
    int *array;
    size_t i;

    array = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_int();

    binary_insertion_sort(array, size, sizeof(int), int_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(int), int_comparator));

    free(array);
}

static void binary_insertion_sort_test_int_array_10(void)
{
    binary_insertion_sort_int_array_test(10);
}

static void binary_insertion_sort_test_int_array_100(void)
{
    binary_insertion_sort_int_array_test(100);
}

static void binary_insertion_sort_test_int_array_1000(void)
{
    binary_insertion_sort_int_array_test(1000);
}

static void binary_insertion_sort_test_int_array_10000(void)
{
    binary_insertion_sort_int_array_test(10000);
}

static void binary_insertion_sort_test_int_array_100000(void)
{
    binary_insertion_sort_int_array_test(100000);
}

static void binary_insertion_sort_test_int_array_1000000(void)
{
    binary_insertion_sort_int_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void binary_insertion_sort_float_array_test(int size)
{
    float *array;
    size_t i;

    array = malloc(sizeof(float) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_float();

    binary_insertion_sort(array, size, sizeof(float), float_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(float), float_comparator));

    free(array);
}

static void binary_insertion_sort_test_float_array_10(void)
{
    binary_insertion_sort_float_array_test(10);
}

static void binary_insertion_sort_test_float_array_100(void)
{
    binary_insertion_sort_float_array_test(100);
}

static void binary_insertion_sort_test_float_array_1000(void)
{
    binary_insertion_sort_float_array_test(1000);
}

static void binary_insertion_sort_test_float_array_10000(void)
{
    binary_insertion_sort_float_array_test(10000);
}

static void binary_insertion_sort_test_float_array_100000(void)
{
    binary_insertion_sort_float_array_test(100000);
}

static void binary_insertion_sort_test_float_array_1000000(void)
{
    binary_insertion_sort_float_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void binary_insertion_sort_string_array_test(int size)
{
    char **array;
    size_t i;

    array = malloc(sizeof(char *) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_string();

    binary_insertion_sort(array, size, sizeof(char *), dyn_string_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(char *), dyn_string_comparator));

    for (i = 0; i < size; i++)
        free(array[i]);

    free(array);
}

static void binary_insertion_sort_test_string_array_10(void)
{
    binary_insertion_sort_string_array_test(10);
}

static void binary_insertion_sort_test_string_array_100(void)
{
    binary_insertion_sort_string_array_test(100);
}

static void binary_insertion_sort_test_string_array_1000(void)
{
    binary_insertion_sort_string_array_test(1000);
}

static void binary_insertion_sort_test_string_array_10000(void)
{
    binary_insertion_sort_string_array_test(10000);
}

static void binary_insertion_sort_test_string_array_100000(void)
{
    binary_insertion_sort_string_array_test(100000);
}

static void binary_insertion_sort_test_string_array_1000000(void)
{
    binary_insertion_sort_string_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static size_t threshold;

static void merge_binary_insertion_sort_int_array_test(int size)
{
    int *array;
    size_t i;

    array = malloc(sizeof(int) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_int();

    threshold = rand_threshold();
    printf("<Threshold: %zu>  ", threshold);
    merge_binary_insertion_sort(array, size, sizeof(int), threshold, int_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(int), int_comparator));

    free(array);
}

static void merge_binary_insertion_sort_test_int_array_10(void)
{
    merge_binary_insertion_sort_int_array_test(10);
}

static void merge_binary_insertion_sort_test_int_array_100(void)
{
    merge_binary_insertion_sort_int_array_test(100);
}

static void merge_binary_insertion_sort_test_int_array_1000(void)
{
    merge_binary_insertion_sort_int_array_test(1000);
}

static void merge_binary_insertion_sort_test_int_array_10000(void)
{
    merge_binary_insertion_sort_int_array_test(10000);
}

static void merge_binary_insertion_sort_test_int_array_100000(void)
{
    merge_binary_insertion_sort_int_array_test(100000);
}

static void merge_binary_insertion_sort_test_int_array_1000000(void)
{
    merge_binary_insertion_sort_int_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void merge_binary_insertion_sort_float_array_test(int size)
{
    float *array;
    size_t i;

    array = malloc(sizeof(float) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_float();

    threshold = rand_threshold();
    printf("<Threshold: %zu>  ", threshold);
    merge_binary_insertion_sort(array, size, sizeof(float), threshold, float_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(float), float_comparator));

    free(array);
}

static void merge_binary_insertion_sort_test_float_array_10(void)
{
    merge_binary_insertion_sort_float_array_test(10);
}

static void merge_binary_insertion_sort_test_float_array_100(void)
{
    merge_binary_insertion_sort_float_array_test(100);
}

static void merge_binary_insertion_sort_test_float_array_1000(void)
{
    merge_binary_insertion_sort_float_array_test(1000);
}

static void merge_binary_insertion_sort_test_float_array_10000(void)
{
    merge_binary_insertion_sort_float_array_test(10000);
}

static void merge_binary_insertion_sort_test_float_array_100000(void)
{
    merge_binary_insertion_sort_float_array_test(100000);
}

static void merge_binary_insertion_sort_test_float_array_1000000(void)
{
    merge_binary_insertion_sort_float_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

static void merge_binary_insertion_sort_string_array_test(int size)
{
    char **array;
    size_t i;

    array = malloc(sizeof(char *) * size);

    for (i = 0; i < size; i++)
        array[i] = rand_string();

    threshold = rand_threshold();
    printf("<Threshold: %zu>  ", threshold);
    merge_binary_insertion_sort(array, size, sizeof(char *), threshold, dyn_string_comparator);

    TEST_ASSERT_TRUE(is_array_sorted(array, size, sizeof(char *), dyn_string_comparator));

    for (i = 0; i < size; i++)
        free(array[i]);

    free(array);
}

static void merge_binary_insertion_sort_test_string_array_10(void)
{
    merge_binary_insertion_sort_string_array_test(10);
}

static void merge_binary_insertion_sort_test_string_array_100(void)
{
    merge_binary_insertion_sort_string_array_test(100);
}

static void merge_binary_insertion_sort_test_string_array_1000(void)
{
    merge_binary_insertion_sort_string_array_test(1000);
}

static void merge_binary_insertion_sort_test_string_array_10000(void)
{
    merge_binary_insertion_sort_string_array_test(10000);
}

static void merge_binary_insertion_sort_test_string_array_100000(void)
{
    merge_binary_insertion_sort_string_array_test(100000);
}

static void merge_binary_insertion_sort_test_string_array_1000000(void)
{
    merge_binary_insertion_sort_string_array_test(1000000);
}

/*---------------------------------------------------------------------------------------------------------------*/

void setUp(void) {}

void tearDown(void) {}

int main(void)
{
    srand((unsigned int)time(NULL));
    UNITY_BEGIN();

#ifndef DISABLE_MERGESORT

    printf("====== TESTING 'merge_sort' ======\n");

    printf("TESTING INTEGER ARRAYS.....\n");
    RUN_TEST(merge_sort_test_int_array_10);
    RUN_TEST(merge_sort_test_int_array_100);
    RUN_TEST(merge_sort_test_int_array_1000);
    RUN_TEST(merge_sort_test_int_array_10000);
    RUN_TEST(merge_sort_test_int_array_100000);
    RUN_TEST(merge_sort_test_int_array_1000000);

    printf("TESTING FLOAT ARRAYS.....\n");
    RUN_TEST(merge_sort_test_float_array_10);
    RUN_TEST(merge_sort_test_float_array_100);
    RUN_TEST(merge_sort_test_float_array_1000);
    RUN_TEST(merge_sort_test_float_array_10000);
    RUN_TEST(merge_sort_test_float_array_100000);
    RUN_TEST(merge_sort_test_float_array_1000000);

    printf("TESTING STRING ARRAYS.....\n");
    RUN_TEST(merge_sort_test_string_array_10);
    RUN_TEST(merge_sort_test_string_array_100);
    RUN_TEST(merge_sort_test_string_array_1000);
    RUN_TEST(merge_sort_test_string_array_10000);
    RUN_TEST(merge_sort_test_string_array_100000);
    RUN_TEST(merge_sort_test_string_array_1000000);

#endif

#ifndef DISABLE_QUICKSORT

    printf("====== TESTING 'quick_sort' ======\n");

    printf("TESTING INTEGER ARRAYS.....\n");
    RUN_TEST(quick_sort_test_int_array_10);
    RUN_TEST(quick_sort_test_int_array_100);
    RUN_TEST(quick_sort_test_int_array_1000);
    RUN_TEST(quick_sort_test_int_array_10000);
    RUN_TEST(quick_sort_test_int_array_100000);
    RUN_TEST(quick_sort_test_int_array_1000000);

    printf("TESTING FLOAT ARRAYS.....\n");
    RUN_TEST(quick_sort_test_float_array_10);
    RUN_TEST(quick_sort_test_float_array_100);
    RUN_TEST(quick_sort_test_float_array_1000);
    RUN_TEST(quick_sort_test_float_array_10000);
    RUN_TEST(quick_sort_test_float_array_100000);
    RUN_TEST(quick_sort_test_float_array_1000000);

    printf("TESTING STRING ARRAYS.....\n");
    RUN_TEST(quick_sort_test_string_array_10);
    RUN_TEST(quick_sort_test_string_array_100);
    RUN_TEST(quick_sort_test_string_array_1000);
    RUN_TEST(quick_sort_test_string_array_10000);
    RUN_TEST(quick_sort_test_string_array_100000);
    RUN_TEST(quick_sort_test_string_array_1000000);

#endif

#ifndef DISABLE_MERGEBININSSORT

    printf("====== TESTING 'merge_binary_insertion_sort' ======\n");

    printf("TESTING INTEGER ARRAYS.....\n");
    RUN_TEST(merge_binary_insertion_sort_test_int_array_10);
    RUN_TEST(merge_binary_insertion_sort_test_int_array_100);
    RUN_TEST(merge_binary_insertion_sort_test_int_array_1000);
    RUN_TEST(merge_binary_insertion_sort_test_int_array_10000);
    RUN_TEST(merge_binary_insertion_sort_test_int_array_100000);
    RUN_TEST(merge_binary_insertion_sort_test_int_array_1000000);

    printf("TESTING FLOAT ARRAYS.....\n");
    RUN_TEST(merge_binary_insertion_sort_test_float_array_10);
    RUN_TEST(merge_binary_insertion_sort_test_float_array_100);
    RUN_TEST(merge_binary_insertion_sort_test_float_array_1000);
    RUN_TEST(merge_binary_insertion_sort_test_float_array_10000);
    RUN_TEST(merge_binary_insertion_sort_test_float_array_100000);
    RUN_TEST(merge_binary_insertion_sort_test_float_array_1000000);

    printf("TESTING STRING ARRAYS.....\n");
    RUN_TEST(merge_binary_insertion_sort_test_string_array_10);
    RUN_TEST(merge_binary_insertion_sort_test_string_array_100);
    RUN_TEST(merge_binary_insertion_sort_test_string_array_1000);
    RUN_TEST(merge_binary_insertion_sort_test_string_array_10000);
    RUN_TEST(merge_binary_insertion_sort_test_string_array_100000);
    RUN_TEST(merge_binary_insertion_sort_test_string_array_1000000);

#endif

#ifndef DISABLE_BININSSORT

    printf("====== TESTING 'binary_insertion_sort' ======\n");

    printf("TESTING INTEGER ARRAYS.....\n");
    RUN_TEST(binary_insertion_sort_test_int_array_10);
    RUN_TEST(binary_insertion_sort_test_int_array_100);
    RUN_TEST(binary_insertion_sort_test_int_array_1000);
    RUN_TEST(binary_insertion_sort_test_int_array_10000);
    RUN_TEST(binary_insertion_sort_test_int_array_100000);
    RUN_TEST(binary_insertion_sort_test_int_array_1000000);

    printf("TESTING FLOAT ARRAYS.....\n");
    RUN_TEST(binary_insertion_sort_test_float_array_10);
    RUN_TEST(binary_insertion_sort_test_float_array_100);
    RUN_TEST(binary_insertion_sort_test_float_array_1000);
    RUN_TEST(binary_insertion_sort_test_float_array_10000);
    RUN_TEST(binary_insertion_sort_test_float_array_100000);
    RUN_TEST(binary_insertion_sort_test_float_array_1000000);

    printf("TESTING STRING ARRAYS.....\n");
    RUN_TEST(binary_insertion_sort_test_string_array_10);
    RUN_TEST(binary_insertion_sort_test_string_array_100);
    RUN_TEST(binary_insertion_sort_test_string_array_1000);
    RUN_TEST(binary_insertion_sort_test_string_array_10000);
    RUN_TEST(binary_insertion_sort_test_string_array_100000);
    RUN_TEST(binary_insertion_sort_test_string_array_1000000);

#endif

    return UNITY_END();
}