#include<stdio.h>
#include<stdlib.h>
#include"cdio.h"
#include"constants.h"
#include"errors_processing.h"
#include"program.h"

#include"structs.h"
#include<inttypes.h>

extern int errno;

#define OK 1
#define NOT_OK 0

/* Input
 * m, n, A
 * p, q, B
 * z,y
 * Output
 * A2^z*B2^y
 *
 * 1 - пустой ввод
 * 2 - некорректные размеры матрицы
 * 3 - корректные размеры матрицы, введеных элементов меньше чем нужно
 * 4 - корректные размеры матрицы, некорректные элементы
 * 5 - корректно введенные матрицы не введено z или y
 * 6 - корректно введенные матрицы не корректные z или y
 * 7 - корректно введенные матрицы, корректно введенные z и y, претендентов на удаление больше, чем надо удалить.
 * Корректно введенные матрицы, корректно введенные z и y
 *   8 - все элементы положительные
 *   9 - все элементы отрицательные
 *   10 - все элементы одинаковые
 *   11 - есть и положительные и отрицательные элементы */
int64_t compare(matrix_t const *const matrix, matrix_t const *const expected_matrix)
{
    for (int64_t i = 0; i < expected_matrix->rows; i++)
    {
        for (int64_t j = 0; j < expected_matrix->columns; j++)
        {
            if (matrix->matrix[i][j] != expected_matrix->matrix[i][j])
            {
                return NOT_OK;
            }
        }
    }
    return OK;
}

void f2d_min_e5t_all_e6s_are_p6v()
{
    errno = SUCCESS;
    printf("All elements are positive ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    int64_t row, column;
    find_last_min_element(&matrix, &row, &column);
    if (errno == SUCCESS && row == 0 && column == 0)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void f2d_min_e5t_all_e6s_are_n6e()
{
    errno = SUCCESS;
    printf("All elements are negative ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = (i + j) * (-1);
    int64_t row, column;
    find_last_min_element(&matrix, &row, &column);
    if (errno == SUCCESS && row == 1 && column == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void f2d_min_e5t_all_e6s_are_s2e()
{
    errno = SUCCESS;
    printf("All elements are the same ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = 5;
    int64_t row, column;
    find_last_min_element(&matrix, &row, &column);
    if (errno == SUCCESS && row == 1 && column == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void r4e_c5s_i6e()
{
    errno = SUCCESS;
    printf("Increase columns: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    resize_columns(&matrix, 3);
    if (errno == SUCCESS && matrix.columns == 7 && matrix.rows == 4)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void r4e_c5s_r4e()
{
    errno = SUCCESS;
    printf("Reduce columns: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    resize_columns(&matrix, -2);
    if (errno == SUCCESS && matrix.columns == 2 && matrix.rows == 4)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void r4e_r2s_i6e()
{
    errno = SUCCESS;
    printf("Increase rows: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    for (int64_t i = 0; i < 3; i++)
        resize_rows(&matrix, 1, 0);
    if (errno == SUCCESS && matrix.rows == 7 && matrix.columns == 4)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void r4e_r2s_r4e()
{
    errno = SUCCESS;
    printf("Reduce rows: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    resize_rows(&matrix, -1, 0);
    if (errno == SUCCESS && matrix.columns == 4 && matrix.rows == 3)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void d4e_row_n6e_row()
{
    errno = SUCCESS;
    printf("Row < 0: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    delete_row(&matrix, -1);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void d4e_row_too_mach_row()
{
    errno = SUCCESS;
    printf("Row > matrix.rows: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    delete_row(&matrix, 5);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void d4e_row_c5t_row()
{
    int64_t check;
    errno = SUCCESS;
    printf("Correct row: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(1, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = i + j;

    delete_row(&matrix, 1);
    if (errno == SUCCESS && matrix.rows == 1)
    {
        check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
            return;
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
        return;
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
    delete_matrix(&expected_matrix);
}

void d4t_c4n_n6e_c4n()
{
    errno = SUCCESS;
    printf("Column < 0: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    delete_column(&matrix, -1);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void d4t_c4n_too_mach_c4n()
{
    errno = SUCCESS;
    printf("Column > matrix.columns: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    delete_column(&matrix, 6);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("SUCCESS\n");
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void d4t_c4n_c5t_c4n()
{
    errno = SUCCESS;
    int64_t check;
    printf("Correct column: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(2, 3, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;
    delete_column(&matrix, 3);
    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = i + j;

    if (errno == SUCCESS && matrix.columns == 3)
    {
        check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
            return;
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
        return;
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
    delete_matrix(&expected_matrix);
}

void m2e_s4e_m4x_w2h_d4e_c5s()
{
    errno = SUCCESS;
    printf("With delete columns: ");
    matrix_t matrix;
    create_matrix(2, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(2, 2, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;

    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = matrix.matrix[i][j + 2];

    make_square_matrix(&matrix);

    if (errno == SUCCESS && matrix.columns == expected_matrix.columns && matrix.rows == expected_matrix.rows)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }    
}

void m2e_s4e_m4x_w2h_d4e_r2s()
{
    errno = SUCCESS;
    printf("With delete rows: ");
    matrix_t matrix;
    create_matrix(6, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(4, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;

    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = matrix.matrix[i + 2][j];

    make_square_matrix(&matrix);

    if (errno == SUCCESS && matrix.columns == expected_matrix.columns && matrix.rows == expected_matrix.rows)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void m2e_s4e_m4x_e6s_s2e()
{
    errno = SUCCESS;
    printf("All elements are the same: ");
    matrix_t matrix;
    create_matrix(6, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(4, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = 6;

    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = 6;

    make_square_matrix(&matrix);

    if (errno == SUCCESS && matrix.columns == expected_matrix.columns && matrix.rows == expected_matrix.rows)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void m2e_s4e_m4x_from_s4e_m4x()
{
    errno = SUCCESS;
    printf("Matrix is already square: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    matrix_t expected_matrix;
    create_matrix(4, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;

    for (int64_t i = 0; i < expected_matrix.rows; i++)
        for (int64_t j = 0; j < expected_matrix.columns; j++)
            expected_matrix.matrix[i][j] = i + j;

    make_square_matrix(&matrix);

    if (errno == SUCCESS && matrix.columns == expected_matrix.columns && matrix.rows == expected_matrix.rows)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void f2l_row_all_e6s_s2e()
{
    errno = SUCCESS;
    printf("All elements are the same: ");
    matrix_t matrix;
    create_matrix(6, 4, &matrix);
    for (int64_t i = 0; i < matrix.rows - 2; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = 6;

    fill_row(&matrix, 4);

    if (errno == SUCCESS)
    {
        for (int64_t j = 0; j < matrix.columns; j++)
        {
            if (matrix.matrix[4][j] != 6)
            {
                printf("FAIL\n");
                delete_matrix(&matrix);
            }
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
    }    
}

void f2l_row_all_e6s_p6e()
{
    errno = SUCCESS;
    printf("All elements are positive: ");
    matrix_t matrix;
    matrix_t expected_matrix;
    create_matrix(6, 4, &matrix);
    create_matrix(5, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows - 2; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = i + j;

    for (int64_t i = 0; i < matrix.rows - 2; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            expected_matrix.matrix[i][j] = i + j;

    expected_matrix.matrix[4][0] = 0;
    expected_matrix.matrix[4][1] = 2;
    expected_matrix.matrix[4][2] = 3;
    expected_matrix.matrix[4][3] = 4;

    fill_row(&matrix, 4);

    if (errno == SUCCESS)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void f2l_row_all_e6s_n6e()
{
    errno = SUCCESS;
    printf("All elements are negative: ");
    matrix_t matrix;
    matrix_t expected_matrix;
    create_matrix(6, 4, &matrix);
    create_matrix(5, 4, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows - 2; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            matrix.matrix[i][j] = (i + j) * (-1);

    fill_row(&matrix, 4);

    for (int64_t i = 0; i < matrix.rows - 2; i++)
        for (int64_t j = 0; j < matrix.columns; j++)
            expected_matrix.matrix[i][j] = (i + j) * (-1);

    expected_matrix.matrix[4][0] = 0;
    expected_matrix.matrix[4][1] = 2;
    expected_matrix.matrix[4][2] = 3;
    expected_matrix.matrix[4][3] = 4;

    if (errno == SUCCESS)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
            return;
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
        return;
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void f2l_c4n_all_e6s_s2e()
{
    errno = SUCCESS;
    printf("All elements are the same: ");
    matrix_t matrix;
    create_matrix(4, 6, &matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns - 2; j++)
            matrix.matrix[i][j] = 6;

    fill_columns(&matrix, 4);

    if (errno == SUCCESS)
    {
        for (int64_t i = 0; i < matrix.rows; i++)
        {
            if (matrix.matrix[i][4] != 6)
            {
                printf("FAIL\n");
                delete_matrix(&matrix);
            }
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
    }    
}

void f2l_c4n_all_e6_s_p6e()
{
    errno = SUCCESS;
    printf("All elements are positive: ");
    matrix_t matrix;
    create_matrix(4, 6, &matrix);
    matrix_t expected_matrix;
    create_matrix(4, 5, &expected_matrix);

    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns - 2; j++)
            matrix.matrix[i][j] = i + j;
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns - 2; j++)
            expected_matrix.matrix[i][j] = i + j;

    expected_matrix.matrix[0][4] = 0;
    expected_matrix.matrix[1][4] = 1;
    expected_matrix.matrix[2][4] = 2;
    expected_matrix.matrix[3][4] = 3;

    fill_columns(&matrix, 4);

    if (errno == SUCCESS)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }    
}

void f2l_c4n_all_e6s_n6e()
{
    errno = SUCCESS;
    printf("All elements are negative: ");
    matrix_t matrix;
    matrix_t expected_matrix;
    create_matrix(4, 6, &matrix);
    create_matrix(4, 5, &expected_matrix);
    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns - 2; j++)
            matrix.matrix[i][j] = (i + j) * (-1);

    for (int64_t i = 0; i < matrix.rows; i++)
        for (int64_t j = 0; j < matrix.columns - 2; j++)
            expected_matrix.matrix[i][j] = (i + j) * (-1);

    expected_matrix.matrix[0][4] = -3;
    expected_matrix.matrix[1][4] = -4;
    expected_matrix.matrix[2][4] = -5;
    expected_matrix.matrix[3][4] = -6;

    fill_columns(&matrix, 4);
    if (errno == SUCCESS)
    {
        int64_t check = compare(&matrix, &expected_matrix);
        if (check != OK)
        {
            printf("FAIL\n");
            delete_matrix(&matrix);
            delete_matrix(&expected_matrix);
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix);
        delete_matrix(&expected_matrix);
    }
}

void init_matrix(matrix_t *matrix)
{
    for (int64_t i = 0; i < matrix->rows; i++)
    {
        for (int j = 0; j < matrix->columns; j++)
        {
            matrix->matrix[i][j] = i + j;
        }
    }
}

void add_r2s_c5t_r2s()
{
    errno = SUCCESS;
    printf("Add correct size of rows: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    init_matrix(&matrix);
    add_rows(&matrix, 3);
    if (matrix.rows == 7 && errno == SUCCESS)
    {
        printf("SUCCESS\n");
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);
}

void add_r2s_not_c5t_r2s()
{
    errno = SUCCESS;
    printf("Add not correct size of rows: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    init_matrix(&matrix);
    add_rows(&matrix, -12);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
    {
        printf("SUCCESS\n");
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);    
}

void add_c5s_c5t_c5s()
{
    errno = SUCCESS;
    printf("Add correct size of columns: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    init_matrix(&matrix);
    add_columns(&matrix, 3);
    if (matrix.columns == 7 && errno == SUCCESS)
    {
        printf("SUCCESS\n");
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);    
}

void add_c5s_not_c5t_c5s()
{
    errno = SUCCESS;
    printf("Add not correct size of columns: ");
    matrix_t matrix;
    create_matrix(4, 4, &matrix);
    init_matrix(&matrix);
    add_columns(&matrix, -12);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
    {
        printf("SUCCESS\n");
    }
    else
        printf("FAIL\n");
    delete_matrix(&matrix);    
}

void m2e_s2e_s2e_diff_s2e()
{
    errno = SUCCESS;
    matrix_t matrix_a;
    matrix_t matrix_b;
    create_matrix(4, 4, &matrix_a);
    create_matrix(6, 6, &matrix_b);
    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    make_same_size(&matrix_a, &matrix_b);
    if ((matrix_a.rows == matrix_b.rows) && (matrix_b.columns = matrix_a.columns) && errno == SUCCESS)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
}

void m2e_same_size_not_diff_s2e()
{
    errno = SUCCESS;
    matrix_t matrix_a;
    matrix_t matrix_b;
    create_matrix(6, 6, &matrix_a);
    create_matrix(6, 6, &matrix_b);
    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    make_same_size(&matrix_a, &matrix_b);
    if ((matrix_a.rows == matrix_b.rows) && (matrix_b.columns = matrix_a.columns) && errno == SUCCESS)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
}

void m6y_m4x_not_c5t_s2e()
{
    errno = SUCCESS;
    printf("Not correct size for multiply: ");
    matrix_t matrix_a;
    matrix_t matrix_result;
    matrix_t matrix_b;
    create_matrix(4, 4, &matrix_a);
    create_matrix(6, 6, &matrix_b);
    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    create_matrix(4, 4, &matrix_result);
    multiply_matrix(&matrix_a, &matrix_b, &matrix_result);
    if (errno == NOT_CORRECT_SIZE_FOR_MULTIPLY)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
    delete_matrix(&matrix_result);
}

void m6y_m4x_all_e6s_s2e()
{
    errno = SUCCESS;
    printf("All elements are the same: ");;
    matrix_t matrix_a;
    matrix_t matrix_result;
    matrix_t matrix_b;
    create_matrix(4, 4, &matrix_a);
    create_matrix(4, 4, &matrix_b);
    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    for (int64_t i = 0; i < matrix_a.rows; i++)
        for (int64_t j = 0; j < matrix_a.columns; j++)
            matrix_a.matrix[i][j] = 6;
    for (int64_t i = 0; i < matrix_b.rows; i++)
        for (int64_t j = 0; j < matrix_b.columns; j++)
            matrix_b.matrix[i][j] = 3;
    create_matrix(4, 4, &matrix_result);
    multiply_matrix(&matrix_a, &matrix_b, &matrix_result);
    if (errno == SUCCESS)
    {
        for (int64_t i = 0; i < matrix_result.rows; i++)
        {
            for (int64_t j = 0; j < matrix_result.columns; j++)
            {
                if (matrix_result.matrix[i][j] != 72)
                {
                    printf("FAIL\n");
                    delete_matrix(&matrix_a);
                    delete_matrix(&matrix_b);
                    delete_matrix(&matrix_result);
                }
            }
        }
        printf("SUCCESS\n");
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        delete_matrix(&matrix_result);
    }
    else
    {
        printf("FAIL\n");
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        delete_matrix(&matrix_result);
    }    
}

void c2y_m4x_not_s2e_size()
{
    errno = SUCCESS;
    printf("Not same size of matrix: ");
    matrix_t matrix_a;
    matrix_t matrix_b;
    create_matrix(4, 4, &matrix_a);
    create_matrix(6, 6, &matrix_b);
    init_matrix(&matrix_a);
    init_matrix(&matrix_b);
    copy_matrix(&matrix_a, &matrix_b);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);    
}

void c2y_m4x_s2e_size()
{
    errno = SUCCESS;
    printf("The same size of matrix: ");
    matrix_t matrix_a;
    matrix_t matrix_b;
    create_matrix(6, 8, &matrix_a);
    create_matrix(6, 8, &matrix_b);
    for (int64_t i = 0; i < matrix_a.rows; i++)
    {
        for (int64_t j = 0; j < matrix_a.columns; j++)
        {
            matrix_a.matrix[i][j] = 2;
        }
    }
    init_matrix(&matrix_b);
    copy_matrix(&matrix_a, &matrix_b);
    if (errno == SUCCESS)
    {
        for (int64_t i = 0; i < matrix_a.rows; i++)
        {
            for (int64_t j = 0; j < matrix_a.columns; j++)
            {
                if (matrix_a.matrix[i][j] != matrix_b.matrix[i][j])
                {
                    printf("FAIL\n");
                    delete_matrix(&matrix_a);
                    delete_matrix(&matrix_b);
                    return;
                }
            }
        }
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);    
}

void m4x_in_d4e_not_c5t_d4e()
{
    errno = SUCCESS;
    printf("Not correct degree: ");
    matrix_t matrix_a;
    create_matrix(4, 4, &matrix_a);
    init_matrix(&matrix_a);
    matrix_in_degree(&matrix_a, -1);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);    
}

void m4x_in_d4e_n2l_d4e()
{
    errno = SUCCESS;
    printf("Degree = 0: ");
    matrix_t matrix_a;
    create_matrix(3, 3, &matrix_a);
    init_matrix(&matrix_a);
    matrix_in_degree(&matrix_a, 0);
    if (errno == SUCCESS && matrix_a.matrix[0][0] == 1 && matrix_a.matrix[0][1] == 0 && matrix_a.matrix[0][2] == 0 && \
        matrix_a.matrix[1][0] == 0 && matrix_a.matrix[1][1] == 1 && matrix_a.matrix[1][2] == 0 && matrix_a.matrix[2][0] == 0 \
        && matrix_a.matrix[2][1] == 0 && matrix_a.matrix[2][2] == 1)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);    
}

void m4x_in_d4e_s6d_d4e()
{
    errno = SUCCESS;
    printf("Correct degree = 2: ");
    matrix_t matrix_a;
    create_matrix(2, 2, &matrix_a);
    for (int64_t i = 0; i < matrix_a.rows; i++)
        for (int64_t j = 0; j < matrix_a.columns; j++)
            matrix_a.matrix[i][j] = i + j;
    matrix_in_degree(&matrix_a, 2);
    if (errno == SUCCESS && matrix_a.matrix[0][0] == 1 && matrix_a.matrix[0][1] == 2 && matrix_a.matrix[1][0] == 2 && matrix_a.matrix[1][1] == 5)
    {
        printf("SUCCESS\n");
    }
    else
    {
        printf("FAIL\n");
    }
    delete_matrix(&matrix_a);    
}

int main()
{
    printf("\ntest function find min element:\n");
    f2d_min_e5t_all_e6s_are_p6v();
    f2d_min_e5t_all_e6s_are_n6e();
    f2d_min_e5t_all_e6s_are_s2e();

    printf("\ntest funstion resize columns:\n");
    r4e_c5s_r4e();
    r4e_c5s_i6e();

    printf("\ntest funstion resize rows:\n");
    r4e_r2s_r4e();
    r4e_r2s_i6e();

    printf("\ntest function delete row: \n");
    d4e_row_c5t_row();
    d4e_row_n6e_row();
    d4e_row_too_mach_row();

    printf("\ntest function delete column: \n");
    d4t_c4n_n6e_c4n();
    d4t_c4n_too_mach_c4n();
    d4t_c4n_c5t_c4n();

    printf("\nTest function make square matrix:\n");
    m2e_s4e_m4x_e6s_s2e();
    m2e_s4e_m4x_from_s4e_m4x();
    m2e_s4e_m4x_w2h_d4e_r2s();
    m2e_s4e_m4x_w2h_d4e_c5s();

    printf("\ntest function fill row: \n");
    f2l_row_all_e6s_n6e();
    f2l_row_all_e6s_p6e();
    f2l_row_all_e6s_s2e();

    printf("\ntest function fill column:\n");
    f2l_c4n_all_e6s_n6e();
    f2l_c4n_all_e6_s_p6e();
    f2l_c4n_all_e6s_s2e();

    printf("\nTest function add rows:\n");
    add_r2s_c5t_r2s();
    add_r2s_not_c5t_r2s();

    printf("\nTest function add columns:\n");
    add_c5s_c5t_c5s();
    add_c5s_not_c5t_c5s();

    printf("\ntest function make same size: ");
    m2e_same_size_not_diff_s2e();
    m2e_s2e_s2e_diff_s2e();

    printf("test function multiply matrix:\n");
    m6y_m4x_all_e6s_s2e();
    m6y_m4x_not_c5t_s2e();

    printf("\ntest function matrix in degree:\n");
    m4x_in_d4e_s6d_d4e();
    m4x_in_d4e_n2l_d4e();
    m4x_in_d4e_not_c5t_d4e();

    printf("\ntest finction copy matrix\n");
    c2y_m4x_not_s2e_size();
    c2y_m4x_s2e_size();
}