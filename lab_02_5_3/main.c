#include <stdio.h>
#include <math.h>

#define END_WITH_SUCCES 0
#define INPUT_ERROR 1
#define NOT_CORRECT_VAR 2

#define ONE 1
#define ZERO 0
#define NUMERATOR_DIFF 2
#define NUM_OF_VAR 2

// Вычисление точного значения функции
double exact_val_of_func(double x)
{
    return (ONE / sqrt(ONE - x * x));
}

// Вычисление значения функции с точностью eps
double approximate_func_val(double x, double eps)
{
    double s = 0;
    double temp = 1;
    double numerator = 1;

    while (fabs(temp) > eps)
    {
        s += temp;
        temp = temp * x * x * numerator / (numerator + ONE);
        numerator += NUMERATOR_DIFF;
    }

    return s; 
}

// Вычисление абсолютной ошибки
double count_absol_er(double s_x, double f_x)
{
    return fabs(f_x - s_x);
}

// Вычисление относительной ошибки 
double count_otn_er(double absol_er, double f_x)
{
    return fabs(absol_er / f_x);
}

int count_sum__of_series(short rc, double x, double eps)
{
    double f_x;
    double s_x;
    double absol_er;


    if (rc == NUM_OF_VAR)
    {
        if ((fabs(x) < ONE) && (eps > ZERO) && (eps <= ONE))
        {
            f_x = exact_val_of_func(x);

            s_x = approximate_func_val(x, eps);

            absol_er = count_absol_er(s_x, f_x);

            printf("%lf\n", s_x);
            printf("%lf\n", f_x);
            printf("%lf\n", absol_er);
            printf("%lf\n", count_otn_er(absol_er, f_x));

            return END_WITH_SUCCES;
        }
        else
        {
            printf("Error in varriables.");
            return NOT_CORRECT_VAR;         
        }
    }
    else 
    {
        printf("Input error\n");
        return INPUT_ERROR;
    } 
}

int main(void)
{
    double x;
    double eps;
    short rc;

    rc = scanf("%lf %lf", &x, &eps);

    return count_sum__of_series(rc, x, eps); 
}
