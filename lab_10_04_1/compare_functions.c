#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <math.h>
extern int errno;

double count_mid_mark(double *const arr, const int arr_size)
{
    double result = 0;
    for (int i = 0; i < arr_size; i++)
        result += arr[i];
    return result / arr_size;
}

int compare_surname(student_t const *const a, student_t const *const b)
{
    return strcmp(a->surname, b->surname);
}

int compare_group(student_t const *const a, student_t const *const b)
{
    return strcmp(a->group, b->group);
}

int compare_grade(student_t const *const a, student_t const *const b)
{
    if (a->mid_mark > b->mid_mark)
        return FIRST_MORE;
    if (a->mid_mark < b->mid_mark)
        return FIRST_LESS;
    return EQUIVAL;
}
