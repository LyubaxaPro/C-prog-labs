//Программа получает массив и сортирует его методом вставок.
#include<stdio.h>
#include<math.h>

#define WRONG_NUMBER 1
#define END_WITH_SUCCESS 0

#define ARRAY_SIZE 10

//Считывание массива.
int read_array(int *const array, const int n)
{
    int rc = 0;

    printf("Input array: ");
    for (int i = 0; i < n; i++)
    {
        rc += scanf("%d", &array[i]);
    }

    const char c = getchar();

    if (rc == n && c != ' ')
    {
        return END_WITH_SUCCESS;
    }
    else
    {
        return WRONG_NUMBER;
    }
}

//Сортировка массива
void insertion_sort(int *const array, const int n)
{
    int temp;
    int j;

    for (int i = 1; i < n; i++)
    {
        temp = array[i];
        j = i;

        while (array[i - 1] > temp && j > 0)
        {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = temp;
    }
}

//Вывод массива на экран.
void print_array(const int *const array, const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int get_array_with_current_size(const int rc, const int n, int *const array)
{
    if ((rc != 1 || n > ARRAY_SIZE) || (read_array(array, n) == WRONG_NUMBER))
    {
        return WRONG_NUMBER;
    }
    else
    {
        return END_WITH_SUCCESS;
    }
}

int make_sort_array(int *const array, const int n)
{
    insertion_sort(array, n);
    printf("Sorted array: ");
    print_array(array, n);
    return END_WITH_SUCCESS;
}

int main(void)
{
    int n;
    int array[ARRAY_SIZE];
    int rc = 0;

    printf("Input size of array: ");
    rc = scanf("%d", &n);

    if (get_array_with_current_size(rc, n, array) == END_WITH_SUCCESS)
    {
        return make_sort_array(array, n);
    }
    else
    {
        printf("Wrong number of numbers.");
        return WRONG_NUMBER;
    }
}
