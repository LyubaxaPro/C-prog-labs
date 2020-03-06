#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <stdarg.h>
#include "cdio.h"
#include "memory_functions.h"
extern int errno;

void free_arrays(int n, ...)
{
    va_list arrays;
    va_start(arrays, n);
    for (int i = 0; i < n; i++)
    {
        free(va_arg(arrays, void*));
    }
    va_end(arrays);
}

void resize_x_coefficient(students_t *const students)
{
    student_t *temp = NULL;
    temp = (student_t*)realloc(students->arr, students->buffer_size * COEFFICIENT * sizeof(student_t));
    if (temp == NULL)
    {
        errno = REALLOC_ERROR;
        return;
    }
    students->arr = temp;
    temp = NULL;
    students->buffer_size = students->buffer_size * COEFFICIENT;
}

void create_char_arr(char **arr, const int size)
{
    if (size <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    char *temp = NULL;
    temp = (char*)malloc(sizeof(char) * size);
    if (temp == NULL)
    {
        errno = MALLOC_ERROR;
        return;
    }
    *arr = temp;
    temp = NULL;
}

void create_double_arr(double **arr, const int size)
{
    if (size <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    double *temp = NULL;
    temp = (double*)malloc(sizeof(double) * size);
    if (temp == NULL)
    {
        errno = MALLOC_ERROR;
        return;
    }
    *arr = temp;
    temp = NULL;
}

void reduce_student(students_t *const data, const int index)
{
    if (index > data->cur_size || index < 0)
    { 
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    if (1 == data->cur_size)
    {
        delete(data);
        errno = EMPTY_AFTER_ACT;
        return;
    }
    free_arrays(4, data->arr[index].dob, data->arr[index].group,
    data->arr[index].marks, data->arr[index].surname);
    data->arr[index].marks_size = 0;
    for (int i = index; i < data->cur_size - 1; i++)
    {
        data->arr[i] = data->arr[i + 1];
    }
    student_t *newp = (student_t*)realloc(data->arr, ((data->cur_size - 1) * sizeof(student_t)));
    if (newp == NULL)
    {
        errno = REALLOC_ERROR;
        return;
    }
    data->arr = newp;
    newp = NULL;
    data->cur_size--;
}

void reduce_double_arr(double **arr, const int diff, int *marks_size)
{
    if (*marks_size == diff)
    {
        errno = EMPTY_AFTER_ACT;
        return;
    }

    if (*marks_size < diff || diff < 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    if (diff == 0)
        return;

    double *newp = (double*)realloc(*arr, (*marks_size - diff) * sizeof(double));
    if (newp == NULL)
    {
        errno = REALLOC_ERROR;
        return;
    }
    *arr = newp;
    *marks_size -= diff;
}