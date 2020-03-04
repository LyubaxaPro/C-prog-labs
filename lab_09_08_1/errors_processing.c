#include<stdio.h>
#include"constants.h"
#include"errors_processing.h"

int errno = SUCCESS;

void my_perror()
{
    if (errno == REALLOC_ERROR)
    {
        printf("Realloc error.\n");
    }
    if (errno == MALLOC_ERROR)
    {
        printf("Malloc error.\n");
    }
    if (errno == INPUT_ERROR)
    {
        printf("Input error.\n");
    }
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
    {
        printf("This item is not correct.");
    }
    if (errno == NOT_ENOUGH_ITEMS)
    {
        printf("Do not have enough items.");
    }
    if (errno == NOT_CORRECT_POINTER)
    {
        printf("This item have not correct pointer.");
    }
    if (errno == NOT_CORRECT_SIZE_FOR_MULTIPLY)
    {
        printf("This matrix is wrong.");
    }
}
