#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "test_computation_functions.h"
#include "structs.h"
#include "base_functions.h"
extern int errno;

#define SUCCESS 0
#define CORRECT_ERROR 2
#define MALLOC_ERROR 3
#define ERROR_OF_LIST 4
#define ACTION_LEN 4
#define FALSE 0
#define TRUE 1
#define EMPTY_LIST 5
#define NOT_CORRECT_STR 6
#define ZERO_DIVISION 7

#define ERRNO_PROCESSING(list1, list2, list3) if (errno != SUCCESS) \
{                                 \
    check_list_for_delete(list1); \
    check_list_for_delete(list2); \
    check_list_for_delete(list3); \
    return errno;                 \
}                                 \

#define  MAKE_NUM_AND_ERRNO_CHECK(make_num_exp, errno_exp, list_to_check)   if ((make_num(&list_to_check) == make_num_exp) && (errno == errno_exp)) \
        printf("OK\n");                                                                                                       \
    else                                                                                                                      \
        printf("FAIL\n");                                                                                                     \

#define TEST_ERRNO_CHECK(errno_exp)     if (errno == errno_exp)  \
        printf("OK\n");                                          \
    else                                                         \
        printf("FAIL\n");                                        \

#endif // CONSTANTS_H
