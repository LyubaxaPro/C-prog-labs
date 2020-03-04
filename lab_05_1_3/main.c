//Отсротировать строки матрицы по убыванию их наибольших элементов.

#include <stdio.h>

#define N 10
#define MIN_SIZE 1
#define MATRIX_DIMENSIONAL 2

#define INPUT_ERROR 1
#define END_WITH_SUCCES 0
#define SIZE_ERROR 2
#define ROWS_WITH_IDENTICAL_MAX 3

#define ERROR 0
#define OK 1

typedef int matrix_t[N][N];

//Считывает матрицу в двухмерный массив
int read_matrix(const int n, const int m, matrix_t matrix_arr)
{
    int rc = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            rc += scanf("%d", &matrix_arr[i][j]);
        }
    }

    const char c = getchar();

    if (rc == m * n && c != ' ')
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//Проверяет корректность ведённых размеров матрицы
int check_matrix_size(const int n, const int m, const int rc)
{
    if ((rc == MATRIX_DIMENSIONAL) && (n >= MIN_SIZE && n <= N) && (m >= MIN_SIZE && m <= N))
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}

//Выводит матрицу на экран
void print_matrix(const int n, const int m, matrix_t matrix_arr)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%d ", matrix_arr[i][j]);
        }
        printf("\n");
    }
}

//Переставляет строки матрицы
void change_rows_place(const int n, const int m, matrix_t matrix_arr, const int prev_i)
{
    for (int j = 0; j < m; j++)
    {
        matrix_arr[prev_i][j] = matrix_arr[prev_i - 1][j];
    }
}

//Сортировка массива(принцип сортировки вставками)
int sort_matrix(const int n, const int m, matrix_t matrix_arr)
{
    int temp_arr[N];
    int temp;
    int j;

    int array_of_max_in_rows[N];
    int max_in_row;

    for (int i = 0; i < n; i++)
    {
        max_in_row = matrix_arr[i][0];
        for (int j = 0; j < m; j++)
        {
            if (matrix_arr[i][j] > max_in_row)
            {
                max_in_row = matrix_arr[i][j];
            }
        }

        array_of_max_in_rows[i] = max_in_row;
    }

    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (array_of_max_in_rows[i] == array_of_max_in_rows[j])
            {
                return ERROR;
            }
        }
    }

    for (int i = 1; i < n; i++)
    {
        temp = array_of_max_in_rows[i];
        for (int k = 0; k < m; k++)
        {
            temp_arr[k] = matrix_arr[i][k];
        }
        j = i;
        while (array_of_max_in_rows[j - 1] < temp && j > 0)
        {
            array_of_max_in_rows[j] = array_of_max_in_rows[j - 1];
            change_rows_place(n, m, matrix_arr, j);
            j -= 1;
        }

        array_of_max_in_rows[j] = temp;
        for (int t = 0; t < m; t++)
        {
            matrix_arr[j][t] = temp_arr[t];
        }
    }
    return OK;
}

int get_matrix_with_current_size(const int rc, const int n, const int m, matrix_t matrix_arr)
{
    if (check_matrix_size(n, m, rc) && read_matrix(n, m, matrix_arr))
    {
        return OK;
    }
    else
    {
        return ERROR;
    }
}


int main(void)
{
    int n, m;
    int rc = 0;
    matrix_t matrix_arr;

    rc += scanf("%d %d", &n, &m);

    if (get_matrix_with_current_size(rc, n, m, matrix_arr))
    {
        if (!sort_matrix(n, m, matrix_arr))
        {
            printf("Indentical max in different rows.");
            return ROWS_WITH_IDENTICAL_MAX;
        }
        print_matrix(n, m, matrix_arr);
        return END_WITH_SUCCES;
    }
    else
    {
        printf("Error in matrix size");
        return SIZE_ERROR;
    }
}