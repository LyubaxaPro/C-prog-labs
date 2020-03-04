//удалить строку и столбец, на пересечении которых расположен элемент матрицы,сумма цифр которого минимальна.

#include <stdio.h>

#define N 10
#define MIN_SIZE 2
#define MATRIX_DIMENSIONAL 2

#define INPUT_ERROR 1
#define END_WITH_SUCCES 0
#define SIZE_ERROR 2
#define MUCH_MIN_ELEMENTS 3

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

//Проверяет корректность введённых размеров матрицы
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

//Считает сумму цифр числа
int count_summ_of_number(int n)
{
    int sum = 0;
    if (n < 0)
    {
        n *= (-1);
    }

    while (n > 0)
    {
        sum += n % 10;
        n = n / 10;
    }
    return sum;
}

//Удаляет строку с индексом row_min
int del_row(const int n, const int m, matrix_t matrix_arr, const int row_min)
{
    for (int i = row_min; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            matrix_arr[i][j] = matrix_arr[i + 1][j];
        }
    }
    return n - 1;
}

//Удаляет столбец с индексом col_min
int del_col(const int n, const int m, matrix_t matrix_arr, const int col_min)
{
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = col_min; j < m; j++)
        {
            matrix_arr[i][j] = matrix_arr[i][j + 1];
        }
    }
    return m - 1;
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

//Находит элемент с минимальной суммой цифр в заданной матрице
int find_el_with_min_sum(const int n, const int m, matrix_t matrix_arr, int *const row_min, int *const col_min)
{
    int min_sum = count_summ_of_number(matrix_arr[0][0]);
    int count_min = 0;
    int sum_for_temp;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            sum_for_temp = count_summ_of_number(matrix_arr[i][j]);

            if (sum_for_temp == min_sum)
            {
                count_min += 1;
            }

            if (sum_for_temp < min_sum)
            {
                count_min = 1;
                min_sum = sum_for_temp;
                *row_min = i;
                *col_min = j;
            }
        }
    }
    return count_min;
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
    int row_min = 0;
    int col_min = 0;

    rc += scanf("%d %d", &n, &m);

    if (get_matrix_with_current_size(rc, n, m, matrix_arr) == ERROR)
    {
        printf("Input error");
        return INPUT_ERROR;
    }

    if (find_el_with_min_sum(n, m, matrix_arr, &row_min, &col_min))
    {
        const int new_n = del_row(n, m, matrix_arr, row_min);
        const int new_m = del_col(n, m, matrix_arr, col_min);
        print_matrix(new_n, new_m, matrix_arr);
        return END_WITH_SUCCES;
    }
    else
    {
        printf("Too many minimal elements.");
        return MUCH_MIN_ELEMENTS;
    }
}
