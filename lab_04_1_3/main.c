//Программа вставляет после каждого числа в  массиве, кратного трём, очередное число Фибоначчи.

#include<stdio.h>
#include<math.h>

#define WRONG_NUMBER 1
#define END_WITH_SUCCESS 0
#define HAVE_NOT_MULTIPLES_NUMBERS 2

#define ARRAY_SIZE 20
#define FIB_ARRAY_SIZE 10
#define MULTIPLICITY_NUMBER 3

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

//Формирует массив из первых десяти чисел Фибоначчи.
//Находим только 10 чисел так как это максимально возможное количество используемых чисел.
void make_fibonacci_array(int *const fibonacci_array)
{
    fibonacci_array[0] = 0;
    fibonacci_array[1] = 1;
    for (int i = 2; i < FIB_ARRAY_SIZE; i++)
    {
        fibonacci_array[i] = fibonacci_array[i - 1] + fibonacci_array[i - 2];
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

//Изменение массива с числами Фибоначчи после чисел, кратных трём.
void make_array_with_fibonacci(int *const array, int *const n)
{
    int fibonacci_array[ARRAY_SIZE];

    int temp_fibonacci = 0;
    int count_prev_array = 0;
    int i = 0;

    make_fibonacci_array(fibonacci_array);

    while (count_prev_array < *n)
    {
        if (array[i] % MULTIPLICITY_NUMBER == 0)
        {
            for (int j = *n + temp_fibonacci - 1; j > i; j--)
            {
                array[j + 1] = array[j];
            }
            array[i + 1] = fibonacci_array[temp_fibonacci];
            temp_fibonacci += 1;
            i += 1;
        }
        count_prev_array += 1;
        i += 1;
    }

    *n += temp_fibonacci;
}

int get_array_with_current_size(const int rc, const int n, int *const array)
{
    if ((rc != 1) || (n > ARRAY_SIZE) || (read_array(array, n) == WRONG_NUMBER))
    {
        return WRONG_NUMBER;
    }
    else
    {
        return END_WITH_SUCCESS;
    }
}

int main(void)
{
    int n;
    int array[ARRAY_SIZE];
    int rc = 0;

    printf("Input size of array: ");
    rc = scanf("%d", &n);

    if (get_array_with_current_size(rc, n, array) == WRONG_NUMBER)
    {
        printf("Wrong number of numbers");
        return WRONG_NUMBER;
    }
	
    make_array_with_fibonacci(array, &n);
    printf("Array with numbers of Fibonacci: ");
    print_array(array, n);
    return END_WITH_SUCCESS;
}
