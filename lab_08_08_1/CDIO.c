#include<stdio.h>
#include<stdlib.h>
#include "CDIO.h"
#include "program.h"
#include "errors_processing.h"

extern int errno;
//Создание массива из n элементов
void create(p_arr *arr, p_arr *arr_end)
{
    int n;
    double *a = NULL;
    //printf("Input n: ");
    if (scanf ("%d", &n) != OK_SCANF)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (n <= 0)
    {
        errno = SIZE_ERROR;
        return;
    }
    a = malloc(n * sizeof(double));

    if (a == NULL)
    {
        errno = ERROR_ALLOCATION;
        return;
    }

    *arr = a;
    *arr_end = a + n;
}

// Печать массива
void output(p_arr const arr, p_arr const arr_end)
{
    for (double *p = arr; p < arr_end; p ++)
    {
        printf("%lf ", *p);
    }
    printf("\n");
}

void input(p_arr arr, p_arr arr_end)
{
    int count = 0;
    for (double *p = arr; p < arr_end; p += 1)
    {
        if (scanf("%lf", p) != OK_SCANF)
        {
            errno = CORRECT_NUMB_ERROR;
            return;
        }
        count++;
    }
    if (arr_end - arr != count)
    {
        errno = ARR_SIZE_ERROR;
        return;
    }
}

// Удаление заданного количества элементов с конца массива
void delete(p_arr *arr, p_arr *arr_end, const int count_el_for_del)
{
    if (*arr_end - *arr == count_el_for_del)
    {
        errno = ALL_EL_WERE_DELETED;
        return;
    }
    if (*arr_end - *arr < count_el_for_del || count_el_for_del <= 0)
    {
        errno = ARR_SIZE_ERROR;
        return;
    }

    resize_arr(arr, arr_end, count_el_for_del * (-1));
}
