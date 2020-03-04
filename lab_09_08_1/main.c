#include<stdio.h>
#include<stdlib.h>
#include"cdio.h"
#include"constants.h"
#include"errors_processing.h"
#include"program.h"
#include<math.h>

#include"structs.h"

extern int errno;

/* Задание
 * Принять с консоли две матрицы.
 * Удаляя строки или столбцы с минимальным элементов в матрице привести их к квадратному виду A1, B1.
 * Если обнаружено несколько, считать целевым минимум, который был бы встречен последним при обходе по столбцам. Если у матрицы больше строк, чем столбцов, то удалять нужно только
 * строки, иначе — только столбцы.
 * Добавляя в конец сначала строки, а потом столбцы привести матрицы 𝐴1 и 𝐵1 к одному размеру 𝐴2 и 𝐵2.
 * Добавлять в новые строки округлённые к нижнему целому средние геометрические модулей элементов столбцов.
 * Добавлять в новые столбцы минимумы по строкам.
 * Приняв с клавиатуры целые неотрицательные z и y, вычислить и вывести на экран результат выражения: A2*A2...*A2(z раз)*B2*B2...B2(y раз).*/

int main()
{
    matrix_t matrix_a;
    matrix_t matrix_b;
    int64_t rows, columns;
    input_matrix_size(&rows, &columns);
    if (errno != SUCCESS)
    {
        my_perror();
        return errno;
    }

    create_matrix(rows, columns, &matrix_a);
    if (errno != SUCCESS)
    {
        my_perror();
        return errno;
    }

    input_matrix(&matrix_a);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        my_perror();
        return errno;
    }


    input_matrix_size(&rows, &columns);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        my_perror();
        return errno;
    }

    create_matrix(rows, columns, &matrix_b);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        my_perror();
        return errno;
    }

    input_matrix(&matrix_b);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    make_square_matrix(&matrix_a);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    make_square_matrix(&matrix_b);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    make_same_size(&matrix_a, &matrix_b);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    int64_t matrix_a_degree, matrix_b_degree;
    input_matrix_degree(&matrix_a_degree, &matrix_b_degree);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    matrix_in_degree(&matrix_a, matrix_a_degree);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    matrix_in_degree(&matrix_b, matrix_b_degree);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }

    matrix_t matrix_result;
    create_matrix(matrix_b.rows, matrix_b.columns, &matrix_result);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        my_perror();
        return errno;
    }
    multiply_matrix(&matrix_a, &matrix_b, &matrix_result);
    if (errno != SUCCESS)
    {
        delete_matrix(&matrix_a);
        delete_matrix(&matrix_b);
        delete_matrix(&matrix_result);
        my_perror();
        return errno;
    }
    printf("Matrix result\n");
    output_matrix(&matrix_result);


    delete_matrix(&matrix_a);
    delete_matrix(&matrix_b);
    delete_matrix(&matrix_result);
    return SUCCESS;
}
