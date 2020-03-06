#ifndef CONSTANTS_H
#define CONSTANTS_H

#define SUCCESS 0
#define OK_SCANF 1
#define REALLOC_ERROR 2
#define MALLOC_ERROR 3
#define INPUT_ERROR 4
#define NOT_CORRECT_SIZE_OF_VAL 5
#define NOT_ENOUGH_ITEMS 6
#define WRONG_SIZE 7
#define FOPEN_ERROR 8
#define EMPTY_AFTER_ACT 9

#define EPS 0.0000001
#define EQUIVAL 0
#define FIRST_LESS -1
#define FIRST_MORE 1
#define TRUE 1
#define FALSE 0

#define CREATE_ERROR if (errno != SUCCESS)    \
{                                             \
    my_perror();                              \
    return errno;                             \
}                                             \

#define PERROR(delete_student)      if (errno != SUCCESS)     \
{                                                             \
    my_perror();                                              \
    if (delete_student == TRUE)                               \
        delete(&students);                                    \
    return errno;                                             \
}

#define ERRNO_ALLOCATION_CHECK if (errno != SUCCESS) \
{                                                    \
    my_perror();                                     \
    return;                                          \
}                                                    \

#define  ERRNO_COMPARE(expected_value)   if (errno == expected_value)   \
        printf("OK\n");                                                 \
    else                                                                \
        printf("FAIL\n");                                               \

#define STR_SIZE_FOR_FIELD 10
#define TRUE 1
#define FALSE 0

#define MAX_STR_SIZE 256
#define TOO_LONG_STR 7
#define DOB_SIZE 10
#define START_BUFFER_SIZE 4
#define COEFFICIENT 2

#define JANUARY 1
#define FEBRUARY 2
#define MARCH 3
#define APRIL 4
#define MAY 5
#define JUNE 6
#define JULY 7
#define AUGUST 8
#define SEPTEMBER 9
#define OCTOBER 10
#define NOVEMBER 11
#define DECEMBER 12

#define POINT_AFTER_YEAR 4
#define POINT_AFTER_MONTH 7
#define POINT_AFTER_DAY 10

#define CURRENT_YEAR 2019
#define CURRENT_MONTH 11
#define CURRENT_DAY 1

#define AGE_FOR_DELETE 17
#define MARK_FOR_DEL 4.0

#endif // CONSTANTS_H
