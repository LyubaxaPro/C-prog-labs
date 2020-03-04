//По матрице получить одномерный массив, присвоив его k-тому элементу значение 1, если
//k-ая строка симметрична, и значение 0 иначе.

#include <stdio.h>

#define N 10
#define MIN_SIZE 1
#define INPUT_ERROR 1
#define END_WITH_SUCCES 0

#define ERROR 0
#define OK 1
#define MATRIX_DIMENSIONAL 2

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

//Проверяет строку матрицы на симметричность
int check_line(int arr[], const int m)
{
    for (int j = 0; j < m / 2; j++)
    {
        if (arr[j] != arr[m - j - 1])
        {
            return ERROR;
        }
    }
    return OK;
}

//Выводит массив на экран
void print_array(const int n, int array[])
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

//Составляет массив-ответ
void make_answ_arr(const int n, const int m, matrix_t matrix_arr, int answ_arr[N])
{
    for (int i = 0; i < n; i++)
    {
        answ_arr[i] = check_line(matrix_arr[i], m);
    }
}


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
    int answ_arr[N];

    rc += scanf("%d %d", &n, &m);

    if (get_matrix_with_current_size(rc, n, m, matrix_arr))
    {
        make_answ_arr(n, m, matrix_arr, answ_arr);
        print_array(n, answ_arr);

        return END_WITH_SUCCES;
    }
    else
    {
        printf("Input error");
        return INPUT_ERROR;
    }
}
