#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define SUCCESS 0
//Посчитать дисперсию.

#define DONT_HAVE_FILENAME -1
#define FILE_ERROR -2
#define EMPTY_FILE -3
#define UNEXPECTED_VALUE -4
#define TRUE_SIMBOL 1

//Вычисление математического ожидания
double mathematical_expectation(FILE *f, int *flag, int *count)
{
    double sum = 0;
    double num;

    if ((fscanf(f, "%lf", &num) != TRUE_SIMBOL) && (feof(f)))
    {
        fprintf(stderr, "Empty\n");
        *flag = EMPTY_FILE;
        return EMPTY_FILE;
    }
    else
    {
        sum += num;
        *count += 1;
    }

    while (fscanf(f, "%lf", &num) == TRUE_SIMBOL)
    {
        *count += 1;
        sum += num;
    }

    if ((fscanf(f, "%lf", &num) != TRUE_SIMBOL) && (!feof(f)))
    {
        *flag = UNEXPECTED_VALUE;
        return UNEXPECTED_VALUE;
    }
    return sum / *count;
}

//Вычисление дисперсии
double dispersion(FILE *f, const double mathematical_expectation, const int count)
{
    double num;
    double numerator = 0;
    while (fscanf(f, "%lf", &num) == TRUE_SIMBOL)
    {
        numerator += (num - mathematical_expectation) * (num - mathematical_expectation);
    }
    return (numerator) / count;
}


int main(int argc, char **argv)
{
    int flag = SUCCESS;
    int count = 0;
    FILE *f;

    if (argc != 2)
    {
        fprintf(stderr, "num_reader.exe <file-name>\n");
        flag = DONT_HAVE_FILENAME;
    }

    f = fopen(argv[1], "r");

    if (f == NULL)
    {
        fprintf(stderr, "I/O error\n");
        flag = FILE_ERROR;
    }

    if (flag == SUCCESS)
    {
        const double math_exp = mathematical_expectation(f, &flag, &count);
        fclose(f);

        if (flag == SUCCESS)
        {
            f = fopen(argv[1], "r");
            printf("%.4lf", dispersion(f, math_exp, count));
            fclose(f);
        }
    }
    else
    {
        fclose(f);
    }

    return flag;
}
