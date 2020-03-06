#include <stdio.h>
#include <stdlib.h>
#include "errors_processing.h"
#include "memory_functions.h"
#include "check_functions.h"
#include "program.h"
#include "constants.h"
#include "cdio.h"
#include <string.h>
extern int errno;

void create(students_t *const data)
{
    student_t *temp = (student_t*)malloc(START_BUFFER_SIZE * sizeof(student_t));
    if (temp == NULL)
    {
        errno = MALLOC_ERROR;
        return;
    }
    data->arr = temp;
    data->buffer_size = START_BUFFER_SIZE;
}

void delete(students_t *const data)
{
    if (data->buffer_size == 0)
        return;
    for (int i = 0; i < data->cur_size; i++)
    {
        free_arrays(3, data->arr[i].group, data->arr[i].surname, data->arr[i].dob);
        if (data->arr[i].marks_size != 0)
            free(data->arr[i].marks);
    }
    free(data->arr);
    data->cur_size = 0;
    data->buffer_size = 0;
}

void output(students_t const *const data)
{
    FILE *f = fopen("students.txt", "w");
    if (f == NULL)
    {
        errno = FOPEN_ERROR;
        return;
    }
    for (int i = 0; i < data->cur_size; i++)
    {
        fprintf(f, "%s\n%s\n%s\n%d ", data->arr[i].group, data->arr[i].surname, data->arr[i].dob, data->arr[i].marks_size);
        for (int j = 0; j < data->arr[i].marks_size; j++)
        {
            fprintf(f, "%lf ", data->arr[i].marks[j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

void input(students_t *const data)
{
    char string[MAX_STR_SIZE];
    int flag = 1;
    data->cur_size = 0;
    int size;
    while (flag)
    {
        size = data->cur_size;
        scanf("%s", string);
        if (strcmp(string, "none") == SUCCESS)
        {
            return;
        }

        if (data->cur_size == data->buffer_size)
            resize_x_coefficient(data);

        check_group(string);
        if (errno != SUCCESS)
        {
            return;
        }

        create_char_arr(&data->arr[size].group, strlen(string) + 1);
        if (errno != SUCCESS)
        {
            return;
        }

        for (int i = 0; i <= strlen(string); i++)
            data->arr[size].group[i] = string[i];


        scanf("%s", string);
        check_surname(string);
        if (errno != SUCCESS)
        {
            free_arrays(1, data->arr[size].group);
            return;
        }

        create_char_arr(&data->arr[size].surname, strlen(string) + 1);
        if (errno != SUCCESS)
        {
            free_arrays(1, data->arr[size].group);
            return;
        }

        for (int i = 0; i <= strlen(string); i++)
            data->arr[size].surname[i] = string[i];

        scanf("%s", string);
        check_dob(string);
        if (errno != SUCCESS)
        {
            free_arrays(2, data->arr[size].group, data->arr[size].surname);
            return;
        }

        create_char_arr(&data->arr[size].dob, strlen(string) + 1);
        if (errno != SUCCESS)
        {
            free_arrays(2, data->arr[size].group, data->arr[size].surname);
            return;
        }

        for (int i = 0; i <= strlen(string); i++)
            data->arr[size].dob[i] = string[i];

        int rc = scanf("%d", &data->arr[size].marks_size);
        if (rc != OK_SCANF)
        {
            errno = INPUT_ERROR;
            free_arrays(3, data->arr[size].group, data->arr[size].surname,
            data->arr[size].dob);
            return;
        }

        if (data->arr[size].marks_size <= 0)
        {
            errno = INPUT_ERROR;
            free_arrays(3, data->arr[size].group, data->arr[size].surname,
            data->arr[size].dob);
            return;
        }
        double temp_mark;
        int count_filled_marks = 0;
        create_double_arr(&data->arr[size].marks, data->arr[size].marks_size);
        if (errno != SUCCESS)
        {
            free_arrays(3, data->arr[size].group, data->arr[size].surname,
            data->arr[size].dob);
            return;
        }

        for (int i = 0; i < data->arr[size].marks_size; i++)
        {
            rc = scanf("%lf", &temp_mark);
            if (rc != OK_SCANF || temp_mark < 0)
            {
                errno = INPUT_ERROR;
                free_arrays(4, data->arr[size].group, data->arr[size].surname,
                data->arr[size].dob, data->arr[size].marks);
                data->arr[size].marks_size = 0;
                return;
            }
            data->arr[size].marks[i] = temp_mark;
            count_filled_marks++;
        }

        if (count_filled_marks != data->arr[size].marks_size)
        {
            errno = NOT_ENOUGH_ITEMS;
            free_arrays(4, data->arr[size].group, data->arr[size].surname,
            data->arr[size].dob, data->arr[size].marks);
            data->arr[size].marks_size = 0;
            return;
        }
        data->arr[size].mid_mark = 0;
        data->cur_size++;
    }
}
