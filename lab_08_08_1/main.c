#include<stdio.h>
#include<stdlib.h>

#include "CDIO.h"
#include "program.h"
#include "errors_processing.h"

extern int errno;

int main(void)
{
    double *arr = NULL;
    double *arr_end = NULL;
    int p;

    setbuf(stdout, NULL);

    create(&arr, &arr_end);
    if (errno != SUCCESS)
    {
        my_perror(errno);
        return errno;
    }

    input(arr, arr_end);
    if (errno != SUCCESS)
    {
        my_perror(errno);
        free(arr);
        return errno;
    }

    input_p(&p);
    if (errno != SUCCESS)
    {
        my_perror(errno);
        free(arr);
        return errno;
    }

    double mu1 = count_mu1(arr, arr_end);

    if_delete(&arr, &arr_end, mu1);
    if (errno != SUCCESS)
    {
        my_perror(errno);
        free(arr);
        return errno;
    }

    double mu2 = count_mu2(arr, arr_end);

    if_insert(&arr, &arr_end, p, mu2);
    if (errno != SUCCESS)
    {
        my_perror(errno);
        free(arr);
        return errno;
    }

    output(arr, arr_end);

    free(arr);

    return SUCCESS;
}
