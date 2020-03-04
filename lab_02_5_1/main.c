#include <stdio.h>

#define COUNT_NUM 1
#define ZERO 0
#define MIN_BASE 1
#define K 10

#define END_WITH_SUCCESS 0
#define INPUT_ERROR 1


// Печать одной цифры числа
void to_print(int temp)
{
    printf("%d", temp);
}

void number_processing(long long n, long long base)
{
    while (base != MIN_BASE)
    {
        to_print(n / base);

        n = n % base;
        base = base / K;
    }

    to_print(n);
    printf("\n");		
}

// Нахождение максимальной степени 10, которая <= n
long long count_rank(long long digit)
{
    long long base = MIN_BASE;

    while (K * base <= digit)
    {
        base *= K;
    }
	
    return base;
}

int try_to_print_n(short rc, long long n)
{
    if (rc == COUNT_NUM && n > ZERO)
    {       
        long long base = count_rank(n);
        
        number_processing(n, base);

        return END_WITH_SUCCESS;
    }
    else
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }
}

int main(void)
{
    long long n;
    short rc = scanf("%lli", &n);

    return try_to_print_n(rc, n);
}
