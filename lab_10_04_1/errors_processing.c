#include <stdio.h>
#include "constants.h"
#include <stdlib.h>
#include "errors_processing.h"
#include "structs.h"

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
    if (errno == WRONG_SIZE)
    {
        printf("Wrong size.");
    }
    if (errno == FOPEN_ERROR)
    {
        printf("Fopen errnon.");
    }
    if (errno == EMPTY_AFTER_ACT)
    {
        printf("Array is empty after delete.");
    }
}

