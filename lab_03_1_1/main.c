//Найти два максимальных элемента(возможно одинаковых)

#include<stdio.h>
#define FILE_ERROR 1
#define WRONG_DATA 2
#define END_WITH_SUCCESS 0
#define WRONG_FILE -2
#define TRUE_INPUT 1


//max1 >= max2
int process(FILE *f, int *max1, int *max2)
{
    int i = 0;
    int temp_num;

    if (fscanf(f, "%d", &temp_num) == TRUE_INPUT)
    {
        i += 1;
        *max1 = temp_num;
        if (fscanf(f, "%d", &temp_num) == TRUE_INPUT)
        {
            i += 1;
            *max2 = temp_num;

            if (*max1 < *max2)
            {
                temp_num = *max1;
                *max1 = *max2;
                *max2 = temp_num;
            }

            while (fscanf(f, "%d", &temp_num) == TRUE_INPUT)
            {
                i += 1;
                if (temp_num > *max1)
                {
                    *max2 = *max1;
                    *max1 = temp_num;
                }
                if (temp_num < *max1 && temp_num > *max2)
                {
                    *max2 = temp_num;
                }
            }
        }
    }
    if (i <= 1)
    {
        return WRONG_FILE;
    }
    else
    {
        return END_WITH_SUCCESS;
    }
}
int main(void)
{
    FILE *f = stdin;
    int max1, max2;

    if (f == NULL)
    {
        printf("File error");
        fclose(f);
        return FILE_ERROR;
    }

    if (process(f, &max1, &max2) == END_WITH_SUCCESS)
    {
        printf("Max elements: %d %d", max2, max1);
        fclose(f);
        return END_WITH_SUCCESS;
    }
    else
    {
        printf("There are not enough data.\n");
        fclose(f);
        return WRONG_DATA;
    }
}
