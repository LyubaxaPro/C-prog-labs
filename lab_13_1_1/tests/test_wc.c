#include "test_wc.h"
#include<stdio.h>

void test_wc(int argc, char **argv)
{
    if (wc(argc, argv) == 0)
        printf("\nOk\n");
    else
        printf("\nFail\n");
}

int main(int argc, char **argv)
{
    test_wc(argc, argv);
}