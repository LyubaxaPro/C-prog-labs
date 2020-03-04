#include<stdio.h>
#include"constants.h"
#include"errors_processing.h"


typedef double *p_arr;

int errno = SUCCESS;

void my_perror(const int errno)
{
    if (errno == INPUT_ERROR)
        printf("Wrong input format.\n");
    if (errno == SIZE_ERROR)
        printf("Can not create an array of this size.\n");
    if (errno == ERROR_ALLOCATION)
        printf("Allocation error.\n");
    if (errno == ARR_SIZE_ERROR)
        printf("Array size is not correct.\n");
    if (errno == ALL_EL_WERE_DELETED)
        printf("All elements were deleted.");
    if (errno == REALLOC_ERROR)
        printf("Realloc error\n");
    if (errno == UNCORRECT_POSITION)
        printf("Uncorrect position\n");
    if (errno == CORRECT_NUMB_ERROR)
        printf("Not correct numbers entered.\n");
}

