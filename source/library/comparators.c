#include <string.h>
#include "comparators.h"

int int_comparator(const void *left, const void *right)
{
    int a = *(int *)left;
    int b = *(int *)right;

    if (a > b)
        return 1;
    if (a < b)
        return -1;
    return 0;
}

int float_comparator(const void *left, const void *right)
{
    float a = *(float *)left;
    float b = *(float *)right;

    if (a > b)
        return 1;
    if (a < b)
        return -1;
    return 0;
}

int string_comparator(const void *left, const void *right)
{
    char *a = (char *)left;
    char *b = (char *)right;

    return strcmp(a, b);
}

int dyn_string_comparator(const void *left, const void *right)
{
    char *a = *(char **)left;
    char *b = *(char **)right;

    return strcmp(a, b);
}