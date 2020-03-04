//Программа получает массив и формирует новый, состоящий только из простых чисел введённого массива.
#include<stdio.h>
#include<math.h>

#define WRONG_NUMBER 5
#define END_WITH_SUCCESS 0
#define NOT_SIMPLE 2
#define SIMPLE 0
#define HAVE_NOT_SIMPLE -1
#define OK 1

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

//Проверка числа на простоту.
int check_simplicity(const int a)
{
    for (int i = 2;i <= sqrt(a); i++)
    {
        if (a % i == 0)
        {
            return NOT_SIMPLE;
        }
    }
    return SIMPLE;
}


//Вывод массива на экран.
void print_array(const int *const array, const int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i]);
    }
}

//Формирование массива только из простых чисел.
int make_simple_array(const int *const array, const int n, int *const simple_array, int *const simple_array_size)
{
    int j = 0;
    for (int i = 0; i < n; i++)
    {
        if (array[i] > 1)
        {
            if (check_simplicity(array[i]) == SIMPLE)
            {
                simple_array[j] = array[i];
                j += 1;
                *simple_array_size += 1;
            }
        }
    }
    return (*simple_array_size != 0);
}

int get_array_with_current_size(const int rc, const int n, int *const array)
{
    if ((rc != 1) || (n > ARRAY_SIZE) || (read_array(array, n) == WRONG_NUMBER))
    {
        return WRONG_NUMBER;
    }
    else
    {
        return OK;
    }
}

int main(void)
{
    int n;
    int array[ARRAY_SIZE];
    int rc = 0;
    int simple_array_size = 0;
    int simple_array[ARRAY_SIZE];

    printf("Input size of array: ");
    rc = scanf("%d", &n);

    if (get_array_with_current_size(rc, n, array) == WRONG_NUMBER)
    {
        printf("Wrong number of numbers.");
        return WRONG_NUMBER;
    }
	
    if (make_simple_array(array, n, simple_array, &simple_array_size))
    {
        print_array(simple_array, simple_array_size);
        return END_WITH_SUCCESS;
    }
    else
    {
        printf("Array haven't any simple numbers.");
        return HAVE_NOT_SIMPLE;
    }
}
