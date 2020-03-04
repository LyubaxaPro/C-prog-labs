#include<stdio.h>
#include<stdlib.h>
#include"errors_processing.h"
#include"constants.h"
#include"cdio.h"
#include<inttypes.h>
extern int errno;

void create_matrix(const int64_t rows, const int64_t columns, matrix_t *const temp_matrix)
{
    if (rows <= 0 || columns <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    temp_matrix->matrix = (int64_t**)malloc(sizeof(int64_t*) * rows);
    
    if (temp_matrix->matrix == NULL)
    {
        errno = MALLOC_ERROR;
    }
    int64_t *temp_arr;
    for (int64_t i = 0; i < rows; i++)
    {
        temp_arr = (int64_t*)malloc(sizeof(int64_t) * columns);
        if (temp_arr == NULL)
        {
            errno = MALLOC_ERROR;
            for (int64_t j = 0; j <= i; j++)
                free(temp_matrix->matrix[j]);
            return;
        }
        temp_matrix->matrix[i] = temp_arr;
    }
    temp_arr = NULL;
    temp_matrix->columns = columns;
    temp_matrix->rows = rows;
}

void delete_matrix(matrix_t *const matrix_struct)
{
    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        free(matrix_struct->matrix[i]);
    }
    free(matrix_struct->matrix);
}

void input_matrix(matrix_t *const matrix_struct)
{
    int64_t temp;
    int rc;
    int64_t count = 0;

    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        for (int64_t j = 0; j < matrix_struct->columns; j++)
        {
            if ((rc = scanf("%" PRId64, &temp)) != OK_SCANF)
            {
                errno = INPUT_ERROR;
                return;
            }
            matrix_struct->matrix[i][j] = temp;
            count++;
        }
    }
    if (count != matrix_struct->columns * matrix_struct->rows)
    {
        errno = NOT_ENOUGH_ITEMS;
        return;
    }
}

void output_matrix(matrix_t const *const matrix_struct)
{
    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        for (int64_t j = 0; j < matrix_struct->columns; j++)
        {
            printf("%" PRId64 " ", matrix_struct->matrix[i][j]);
        }
        printf("\n");
    }
}

