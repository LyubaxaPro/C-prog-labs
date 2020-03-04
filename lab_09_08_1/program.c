#include<stdio.h>
#include<stdlib.h>
#include"errors_processing.h"
#include"constants.h"
#include"program.h"
#include<math.h>
#include<inttypes.h>
#include"cdio.h"
extern int errno;

void input_matrix_size(int64_t *const matrix_rows, int64_t *const matrix_columns)
{
    if (scanf ("%" PRId64, matrix_rows) != OK_SCANF)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (*matrix_rows <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    if (scanf ("%" PRId64, matrix_columns) != OK_SCANF)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (*matrix_columns <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
}

void find_last_min_element(matrix_t const *const matrix_struct, int64_t *const row, int64_t *const column)
{
    int64_t min = matrix_struct->matrix[0][0];
    *row = 0;
    *column = 0;
    for (int64_t j = 0; j < matrix_struct->columns; j++)
    {
        for (int64_t i = 0; i < matrix_struct->rows; i++)
        {
            if (matrix_struct->matrix[i][j] <= min)
            {
                *row = i;
                *column = j;
                min = matrix_struct->matrix[i][j];
            }
        }
    }
}

void resize_columns(matrix_t *const matrix_struct, const int64_t diff)
{
    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        int64_t *newp = (int64_t*)realloc(matrix_struct->matrix[i], ((matrix_struct->columns + diff) * sizeof(int64_t)));
        if (newp == NULL)
        {
            errno = REALLOC_ERROR;
            return;
        }
        matrix_struct->matrix[i] = newp;
    }
    matrix_struct->columns += diff;
}

void resize_rows(matrix_t *const matrix_struct, const int64_t diff, const int row)
{
    if (diff == -1)
    {
        free(matrix_struct->matrix[row]);
        for (int64_t i = row; i < matrix_struct->rows - 1; i++)
        {
            matrix_struct->matrix[i] = matrix_struct->matrix[i + 1];
        }
        int64_t **newp = (int64_t**)realloc(matrix_struct->matrix, ((matrix_struct->rows + diff) * sizeof(int64_t*)));
        if (newp == NULL)
        {
            errno = REALLOC_ERROR;
            return;
        }
        matrix_struct->matrix = newp;
        newp = NULL;
        matrix_struct->rows += diff;
    }
    if (diff == 1) 
    {
        int64_t *temp_arr = NULL;
        temp_arr = (int64_t*)malloc(sizeof(int64_t) * matrix_struct->columns);
        if (temp_arr == NULL)
        {
            errno = MALLOC_ERROR;
            return;
        }

        int64_t **newp = (int64_t**)realloc(matrix_struct->matrix, ((matrix_struct->rows + diff) * sizeof(int64_t*)));
        if (newp == NULL)
        {
            errno = REALLOC_ERROR;
            free(temp_arr);
            return;
        }
        matrix_struct->matrix = newp;
        matrix_struct->matrix[matrix_struct->rows] = temp_arr;
        temp_arr = NULL;
        newp = NULL;
        matrix_struct->rows += diff;
    }
}

void delete_row(matrix_t *const matrix_struct, const int64_t row)
{
    if (row < 0 || row >= matrix_struct->rows)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    resize_rows(matrix_struct, -1, row);
}

void delete_column(matrix_t *const matrix_struct, const int64_t column)
{
    if (column < 0 || column >= matrix_struct->columns)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        for (int64_t j = column; j < matrix_struct->columns - 1; j++)
        {
            matrix_struct->matrix[i][j] = matrix_struct->matrix[i][j + 1];
        }
    }
    resize_columns(matrix_struct, -1);
}

void make_square_matrix(matrix_t *const matrix_struct)
{
    int64_t size_diff = abs(matrix_struct->columns - matrix_struct->rows);
    int64_t row_to_del;
    int64_t column_to_del;
    for (int64_t i = 0; i < size_diff; i++)
    {
        find_last_min_element(matrix_struct, &row_to_del, &column_to_del);
        if (matrix_struct->columns > matrix_struct->rows)
        {
            delete_column(matrix_struct, column_to_del);
            if (errno != SUCCESS)
                return;
        }
        else
        {
            delete_row(matrix_struct, row_to_del);
            if (errno != SUCCESS)
                return;
        }
    }
}

void fill_row(matrix_t *const matrix_struct, const int64_t row_to_fill)
{
    int64_t cur;
    for (int64_t j = 0; j < matrix_struct->columns; j++)
    {
        cur = 1;
        for (int64_t i = 0; i < row_to_fill; i++)
        {
            cur *= abs(matrix_struct->matrix[i][j]);
        }
        matrix_struct->matrix[row_to_fill][j] = pow(cur, 1.0 / row_to_fill);
    }
}

void add_rows(matrix_t *const matrix_struct, const int64_t count_rows_to_add)
{
    if (count_rows_to_add <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    int64_t filling_rows = matrix_struct->rows;
    for (int64_t i = 0; i < count_rows_to_add; i++)
    {
        resize_rows(matrix_struct, 1, 0);
        if (errno != SUCCESS)
            return;
    }

    for (int64_t i = filling_rows; i < matrix_struct->rows; i++)
    {
        fill_row(matrix_struct, i);
    }
}

void fill_columns(matrix_t *const matrix_struct, const int64_t column_to_fill)
{
    int64_t min;
    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        min = matrix_struct->matrix[i][0];
        for (int64_t j = 1; j < column_to_fill; j++)
        {
            if (matrix_struct->matrix[i][j] < min)
                min = matrix_struct->matrix[i][j];
        }
        matrix_struct->matrix[i][column_to_fill] = min;
    }
}

void add_columns(matrix_t *const matrix_struct, const int64_t count_columns_to_add)
{
    if (count_columns_to_add <= 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    int64_t filling_columns = matrix_struct->columns;
    resize_columns(matrix_struct, count_columns_to_add);
    if (errno != SUCCESS)
        return;
    for (int64_t j = filling_columns; j < matrix_struct->columns; j++)
    {
        fill_columns(matrix_struct, j);
    }
}

void make_same_size(matrix_t *const matrix_a, matrix_t *const matrix_b)
{
    int64_t diff = abs(matrix_a->columns - matrix_b->columns);
    if (matrix_a->columns > matrix_b->columns)
    {
        add_rows(matrix_b, diff);
        if (errno != SUCCESS)
            return;
        add_columns(matrix_b, diff);
        if (errno != SUCCESS)
            return;
    }
    if (matrix_a->columns < matrix_b->columns)
    {
        add_rows(matrix_a, diff);
        if (errno != SUCCESS)
            return;
        add_columns(matrix_a, diff);
        if (errno != SUCCESS)
            return;
    }
}

void input_matrix_degree(int64_t *const matrix_a_degree, int64_t *const matrix_b_degree)
{
    if (scanf ("%" PRId64, matrix_a_degree) != OK_SCANF)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (*matrix_a_degree < 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    if (scanf ("%" PRId64, matrix_b_degree) != OK_SCANF)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (*matrix_b_degree < 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
}

void multiply_matrix(matrix_t const *const matrix_a, matrix_t const *const matrix_b, matrix_t *const matrix_result)
{
    if (!(matrix_a->rows == matrix_a->columns && matrix_b->rows == matrix_b->columns && matrix_a->columns == matrix_b->columns))
    {
        errno = NOT_CORRECT_SIZE_FOR_MULTIPLY;
        return;
    }

    for (int64_t i = 0; i < matrix_a->rows; i++)
    {
        for (int64_t j = 0; j < matrix_b->rows; j++)
        {
            matrix_result->matrix[i][j] = 0;
            for (int64_t k = 0; k < matrix_b->columns; k++)
            {
                matrix_result->matrix[i][j] += matrix_a->matrix[i][k] * matrix_b->matrix[k][j];
            }
        }
    }
}

void copy_matrix(matrix_t const *const matrix_from, matrix_t *const matrix_to)
{
    if ((matrix_from->rows != matrix_to->rows) || (matrix_from->columns != matrix_to->columns))
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    for (int64_t i = 0; i < matrix_from->rows; i++)
    {
        for (int64_t j = 0; j < matrix_from->columns; j++)
        {
            matrix_to->matrix[i][j] = matrix_from->matrix[i][j];
        }
    }
    matrix_to->rows = matrix_from->rows;
    matrix_to->columns = matrix_from->columns;
}

void make_zero_matrix(matrix_t *const matrix_struct)
{
    if (matrix_struct->columns != matrix_struct->rows)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }
    for (int64_t i = 0; i < matrix_struct->rows; i++)
    {
        for (int64_t j = 0; j < matrix_struct->columns; j++)
        {
            if (i == j)
                matrix_struct->matrix[i][j] = 1;
            else
                matrix_struct->matrix[i][j] = 0;
        }
    }
}

void matrix_in_degree(matrix_t *const matrix_struct, const int64_t degree)
{
    if (degree < 0)
    {
        errno = NOT_CORRECT_SIZE_OF_VAL;
        return;
    }

    if (degree == 0)
    {
        make_zero_matrix(matrix_struct);
        return;
    }

    matrix_t temp_degree_matrix;
    create_matrix(matrix_struct->rows, matrix_struct->columns, &temp_degree_matrix);
    if (errno != SUCCESS)
    {
        return;
    }

    make_zero_matrix(&temp_degree_matrix);

    matrix_t matrix_copy;
    create_matrix(matrix_struct->rows, matrix_struct->columns, &matrix_copy);
    if (errno != SUCCESS)
    {
        delete_matrix(&temp_degree_matrix);
        return;
    }

    copy_matrix(matrix_struct, &matrix_copy);
    if (errno != SUCCESS)
    {
        delete_matrix(&temp_degree_matrix);
        delete_matrix(&matrix_copy);
        return;
    }

    for (int64_t i = 0; i < degree; i++)
    {
        multiply_matrix(&temp_degree_matrix, &matrix_copy, matrix_struct);
        if (errno != SUCCESS)
        {
            delete_matrix(&temp_degree_matrix);
            delete_matrix(&matrix_copy);
            return;
        }

        copy_matrix(matrix_struct, &temp_degree_matrix);
        if (errno != SUCCESS)
        {
            delete_matrix(&temp_degree_matrix);
            delete_matrix(&matrix_copy);
            return;
        }
    }

    delete_matrix(&temp_degree_matrix);
    delete_matrix(&matrix_copy);
}
