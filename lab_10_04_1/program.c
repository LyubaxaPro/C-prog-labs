#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include <stdarg.h>
#include "check_functions.h"
#include "memory_functions.h"
#include "compare_functions.h"
#include "cdio.h"

extern int errno;

void delete_older_than_17(students_t *const data)
{
    int i = 0;
    int count = 0;
    int size = data->cur_size;
    while (i < size - count)
    {
        if (strcmp("ИУ7-31Б\0", data->arr[i].group) == SUCCESS)
        {
            if (check_age_for_delete(&data->arr[i]) == TRUE)
            {
                reduce_student(data, i);
                count++;
                i--;
            }
        }
        i++;
    }
}

void delete_marks_less_4(students_t *const data)
{
    int count;
    int j;
    for (int i = 0; i < data->cur_size; i++)
    {
        j = 0;
        count = 0;
        while (j < data->arr[i].marks_size - count)
        {
            if (data->arr[i].marks[j] < 4.0)
            {
                for (int k = j; k < data->arr[i].marks_size - count - 1; k++)
                    data->arr[i].marks[k] = data->arr[i].marks[k + 1];
                count++;
                j--;
            }
            j++;
        }
        reduce_double_arr(&data->arr[i].marks, count, &data->arr[i].marks_size);
        if (errno != SUCCESS)
        {
            return;
        }
    }
}

void sort_by_field(students_t *const data)
{
    char string[STR_SIZE_FOR_FIELD];
    scanf("%s", string);
    if ((strcmp("GRADE", string)) == SUCCESS)
    {
        for (int i = 0; i < data->cur_size; i++)
        {
            if (data->arr[i].marks_size == 0)
                data->arr[i].mid_mark = 0;
            else
                data->arr[i].mid_mark = count_mid_mark(data->arr[i].marks, data->arr[i].marks_size);
        }
        qsort(data->arr, data->cur_size, sizeof(student_t), (int(*)(const void*, const void*))compare_grade);
        return;
    }

    if ((strcmp("SURNAME", string)) == SUCCESS)
    {
        qsort(data->arr, data->cur_size, sizeof(student_t), (int(*)(const void*, const void*))compare_surname);
        return;
    }

    if ((strcmp("GROUP", string)) == SUCCESS)
    {
        qsort(data->arr, data->cur_size, sizeof(student_t), (int(*)(const void*, const void*))compare_group);
        return;
    }
    errno = INPUT_ERROR;
}




