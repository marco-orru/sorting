#pragma once

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Prints an error message and aborts the execution.
 */
#define PRINT_ERROR(msg, fn)                                  \
    do                                                        \
    {                                                         \
        fprintf(stdout, "RUNTIME_ERROR<" #fn ">: " msg "\n"); \
        fflush(stdout);                                       \
        abort();                                              \
    } while (0)

/**
 * @brief If `cond` is `false`, prints an error message and aborts.
 */
#define ASSERT(cond, msg, fn)     \
    do                            \
    {                             \
        if (!(cond))              \
            PRINT_ERROR(msg, fn); \
    } while (0)

/**
 * @brief If the specified parameter is `null`, prints an error message and aborts.
 */
#define ASSERT_NULL_PARAMETER(param, fn) \
    ASSERT(param, "'" #param "' parameter is NULL", fn)


#if defined(__GNUC__) || defined(__clang__)
/**
 * Indicates unreachable code.
 */
#define UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
/**
 * Indicates unreachable code.
 */
#define UNREACHABLE() __assume(0)
#else
/**
 * Indicates unreachable code.
 */
#define UNREACHABLE() abort()
#endif
