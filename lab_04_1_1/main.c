//Программа предназначена для вычисления произведения нечётных чисел заданного массива.

#include<stdio.h>

#define WRONG_NUMBER 1
#define END_WITH_SUCCESS 0
#define NOT_HAVE_ODD 2

#define ARRAY_SIZE 10

//Считывает массив.
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

//Вычисляет произведение нечётных чисел.
int composition_of_odd(int const *const array, const int n)
{
    int composition = 1;
    int count_digit = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] % 2 != 0)
        {
            composition *= array[i];
            count_digit += 1;
        }
    }
    if (count_digit != 0)
    {
        return composition;
    }
    else
    {
        return NOT_HAVE_ODD;
    }
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

int get_composition_of_odd(int const *const array, const int n)
{
    const int composition = composition_of_odd(array, n);

    if (composition == NOT_HAVE_ODD)
    {
        printf("Array haven't odd.");
        return NOT_HAVE_ODD;
    }
    else
    {
        printf("Composition of odd = %d", composition);
        return END_WITH_SUCCESS;
    }
}

int main(void)
{
    int n;
    int rc = 0;
    int array[ARRAY_SIZE];

    printf("Input size of array: ");
    rc = scanf("%d", &n);

    if (get_array_with_current_size(rc, n, array) == END_WITH_SUCCESS)
    {
        return get_composition_of_odd(array, n);
    }
    else
    {
        printf("Wrong number of numbers"); 
        return WRONG_NUMBER; 
    }
}
