#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include "program.h"
#include "CDIO.h"
#include "errors_processing.h"

extern int errno;

void swap(p_arr a, p_arr b)
{
    double c = *a;
    *a = *b;
    *b = c;
}

// Изменение размера массива
void resize_arr(p_arr *arr, p_arr *arr_end, const int diff_size)
{
    if (diff_size + *arr_end - *arr <= 0)
    {
        errno = ARR_SIZE_ERROR;
        return;
    }
    int n = *arr_end - *arr;

    double *newp = (double*)realloc(*arr, ((diff_size + n) * sizeof(double)));
    if (newp == NULL)
    {
        errno = REALLOC_ERROR;
        return;
    }
    *arr = newp;
    newp = NULL;
    *arr_end = *arr + n + diff_size;
}

// Вставка на позицию position если такое возможно, вставка этого же элемента в начало и конец массива.
void if_insert(p_arr *arr, p_arr *arr_end, const int position, const double mu2)
{   
    if (*arr_end - *arr - 1 < position || position < 0)
    {
        errno = UNCORRECT_POSITION;
        return;
    }
    resize_arr(arr, arr_end, COUNT_EL_FOR_INSERT);
    if (errno != SUCCESS)
        return;
    for (double *p = *arr_end - 2; p > *arr + position + 1; p--)
    {
        *p = *(p - 2);
    }
    *(*arr + position + 1) = mu2;
    for (double *p = *arr + position; p > *arr; p--)
    {
        *p = *(p - 1);
    }
    **arr = mu2;
    *(*arr_end - 1) = mu2;
}

void input_p(int *const p)
{
    int rc;
    if ((rc = scanf("%d", p)) != 1)
    {
        errno = UNCORRECT_POSITION;
    }
    return;
}

// Подсчёт мю1 по формуле среднего арифмитического взвешенного
double count_mu1(p_arr const arr, p_arr const arr_end)
{
    double i = 0;
    double denomirator = 0;
    double numerator = 0;
    for (double *p = arr; p < arr_end; p++)
    {
        numerator += (i + 1) * (i + 1) * (*p);
        denomirator += (i + 1) * (i + 1);
        i++;
    }
    return numerator / denomirator;
}

// Вычисление разницы между модулем числа arr_elem и числом elem_to_diff
double count_diff(const double arr_elem, const double elem_to_diff)
{
    return fabs(fabs(arr_elem) - elem_to_diff);
}

// Подсчёт mu2
double count_mu2(p_arr const arr, p_arr const arr_end)
{
    double summ_of_el = 0;
    for (double *p = arr; p < arr_end; p++)
    {
        summ_of_el += *p;
    }
    return summ_of_el / (arr_end - arr);
}   

void find_two_el_with_max_diff(p_arr const arr, p_arr const arr_end, double *major, double *pre_major, const double mu1)
{
    if (arr_end - arr < 2)
    {
        errno = SIZE_ERROR;
        return;
    }
    double max_diff = 0;
    *major = 0;
    double pre_max_diff = 0;
    *pre_major = 0;
    double temp_diff;
    int flag_m = FALSE;
    int flag_pm = FALSE;

    for (double *p = arr; p < arr_end; p++) 
      // Поиск максимальных разниц
    {
        temp_diff = count_diff(*p, mu1);
        if (temp_diff > max_diff || !flag_m)
        {
            *pre_major = *major;
            pre_max_diff = max_diff;
            max_diff = temp_diff;
            *major = *p;
            if (flag_m)
                flag_pm = TRUE;
            flag_m = TRUE;
        }
        else
        {
            if (temp_diff > pre_max_diff || !flag_pm)
            {
                *pre_major = *p;
                pre_max_diff = temp_diff;
                flag_pm = TRUE;
            }
        }
    }
}


// Удаляет из массива два элемента, имеющих максимальную разницу между между своим модулем и mu1 по порядку следования
void if_delete(p_arr *arr, p_arr *arr_end, const double mu1)
{
    double major, pre_major;
    find_two_el_with_max_diff(*arr, *arr_end, &major, &pre_major, mu1);
    if (errno != SUCCESS)
    {
        return;
    }

    int count_el_for_del = 0;
    double *p = *arr;
    while (p < *arr_end - count_el_for_del && count_el_for_del != 2)
    {
        if (fabs(*p - major) < EPS || fabs(*p - pre_major) < EPS)
        {
            for (double *t = p + 1; t < *arr_end; t++)
            {
                swap(t, t - 1);
            }
            p--;
            count_el_for_del += 1;
        }
        p++;
    }

    delete(arr, arr_end, count_el_for_del);
}