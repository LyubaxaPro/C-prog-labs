#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "CDIO.h"
#include "program.h"
#include "constants.h"
#include "errors_processing.h"

extern int errno;

 /*Input: n, A1, p;
Output: A2;

 1 - пустой ввод
 2 - некорректный размер массива
 3 - корректный размер массива, некорректный элемент массива
 4 - корректный размер массива, корректные элементы массива, элементов меньше чем нужно
 5 - корректный размер массива, корректный массив, не введено p
 6 - корректный размер массива, корректный массив, не корректное  p
 //6 - корректный размер, корректный массив, некорректное n - p - len
 7 - корректный размер, корректный массив, некорректное n - p << 0
 8, 9, 10, 11 - корректный размер, корректный массив, корректное p
    8 - только положительные числа
    9 - только отрицательные числа
    10 - числа значительно разных порядков
    11 - более двух претендентов на удаление
 12 - попытка изменить размер массива на некорректный
*/

/*int TestCreate(void)
{
    printf("Test 0f function create: \n");

    //1
    {
        double* a;
        int n;
        printf("Empty arr ");
        if (create(&a, &n) == INPUT_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
    }

    //2
    {
        double* a;
        int n;
        printf("Not correct size of arr ");
        if (create(&a, &n) == SIZE_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
    }

    //3
    {
        double* a;
        int n;
        printf("Correct size of arr, not correct element of arr ");
        if (create(&a, &n) == CORRECT_NUMB_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
    }

    //4
    {
        double* a;
        int n;
        printf("Correct size of arr, not enough elements of arr ");
        if (create(&a, &n) == ARR_SIZE_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
    }


    //8
    {
        double* a;
        int n;
        printf("Correct size of arr, correct elements of arr ");
        if (create(&a, &n) == SUCCESS)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
    }
    return SUCCESS;

}*/

int test_resize(void)
{
    // 12
    printf("\nTest function resize: \n");
    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Try to resize on uncorrect size: ");
        int diff_size = -11;
        resize_arr(&a, &a_end, diff_size);
        if (errno == ARR_SIZE_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        free(a);
    }

    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Try to resize on correct size: ");
        int diff_size = +11;
        resize_arr(&a, &a_end, diff_size);
        if (errno == SUCCESS)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        
        free(a);
    }
    return SUCCESS;
}

int test_delete(void)
{
    printf("\nTest function delete: \n");
    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Delete all array: ");
        int count_el_for_del = n;
        delete(&a, &a_end, count_el_for_del);
        if (errno == ALL_EL_WERE_DELETED)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        free(a);
    }

    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Delete correct size of array: ");
        int count_el_for_del = 2;
        delete(&a, &a_end, count_el_for_del);
        if (errno == SUCCESS)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        free(a);
    }

    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Delete not correct size of array: ");
        int count_el_for_del = 13;
        delete(&a, &a_end, count_el_for_del);
        if (errno == ARR_SIZE_ERROR)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        free(a);
    }
    return SUCCESS;
}


int test_if_insert(void)
{
    printf("\nTest function if_insert:\n");
    //7
    {
        errno = SUCCESS;
        double expected[] = { 100, 1, 2, 3, 4, 100, 5, 100 };
        double test[] = { 1, 2, 3, 4, 5 };
        int n = 5;
        int expected_n = 8;
// 
        double *a;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;

        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        printf("Correct position: ");
        int position = 4;
        double mu2 = 100;
        i = 0;
        if_insert(&a, &a_end, position, mu2);
        if (errno == SUCCESS)
        {
            if (a_end - a != expected_n)
            {
                printf("FAIL\n");
            }
            else
            {
                for (double *p = a; p < a_end; p++)
                {
                    if (fabs(*p - expected[i]) > EPS)
                    {
                        printf("FAIL\n");
                        break;
                    }
                    i++;
                }
            }
        }
        printf("OK\n");
        free(a);
    }

    {
        errno = SUCCESS;
        double *a;
        int n = 4;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        printf("Not correct position : ");
        int position = 8;
        double mu2 = 1;
        if_insert(&a, &a_end, position, mu2);
        if (errno == UNCORRECT_POSITION)
        {
            printf("OK\n");
        }
        else
            printf("FAIL\n");
        free(a);
    }
    return SUCCESS;
}

int test_count_mu1(void)
{
    printf("\nTest funcriont count_mu1:\n");
    //8
    {
        double test[] = { 1, 2, 3, 4, 5 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_answ = 4.090909;
        printf("Count mu1 with only positiv el: ");
        if (fabs(count_mu1(a, a_end) - expected_answ) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    //9
    {
        double test[] = { -1, -2, -3, -4, -5 };

        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_answ = -4.090909;
        printf("Count mu1 with only negativ el: ");
        if (fabs(count_mu1(a, a_end) - expected_answ) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    //10
    {
        double test[] = { 1.1, 2.00003, 3.145, 4.008, 5.12 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_answ = 4.173329;
        printf("Count mu1 with numbers of diffrenet mantiss: ");
        if (fabs(count_mu1(a, a_end) - expected_answ) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }
    return SUCCESS;
}

int test_count_mu2(void)
{
    printf("\nTest count mu2 ");
    {
        double test[] = { -1, -2, -3, -4, -5 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_answ = -3;
        if (fabs(count_mu2(a, a_end) - expected_answ) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }
    return SUCCESS;
}

int test_find_two_el_with_max_diff(void)
{
    printf("\nTest find_two_el_with_max_diff :\n");
    //8
    {
        double test[] = { 1, 2, 3, 4, 5 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_max_diff_el = 1;
        double expected_pre_max_diff_el = 2;
        double mu1 = 4.090909;
        double max_diff_el;
        double pre_max_diff_el;
        printf("Find max diff elements with only positiv el: ");
        find_two_el_with_max_diff(a, a_end, &max_diff_el, &pre_max_diff_el, mu1);
        if (fabs(max_diff_el - expected_max_diff_el) > EPS || fabs(pre_max_diff_el - expected_pre_max_diff_el) > EPS)
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    //9
    {
        double test[] = { -1, -2, -3, -4, -5 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_max_diff_el = -5;
        double expected_pre_max_diff_el = -4;
        double mu1 = -4.090909;
        double max_diff_el;
        double pre_max_diff_el;
        printf("Find max diff elements with only negativ el: ");
        find_two_el_with_max_diff(a, a_end, &max_diff_el, &pre_max_diff_el, mu1);
        if (fabs(max_diff_el - expected_max_diff_el) > EPS || fabs(pre_max_diff_el - expected_pre_max_diff_el) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    //10
    {
        double test[] = { 1.1, 2.00003, 3.145, 4.008, 5.12 };
        double *a;
        int n = 5;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_max_diff_el = 1.1;
        double expected_pre_max_diff_el = 2.00003;
        double mu1 = 4.173329;
        double max_diff_el;
        double pre_max_diff_el;
        printf("Find max diff elements with numbers of diffrenet mantiss: ");
        find_two_el_with_max_diff(a, a_end, &max_diff_el, &pre_max_diff_el, mu1);
        if (fabs(max_diff_el - expected_max_diff_el) > EPS || fabs(pre_max_diff_el - expected_pre_max_diff_el) > EPS) 
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    //11
    {
        double test[] = { 1, 2, 1, 3, 3, 2, 4, 5 };
        double *a;
        int n = 8;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double expected_max_diff_el = 1;
        double expected_pre_max_diff_el = 1;
        double mu1 = 4.090909;
        double max_diff_el;
        double pre_max_diff_el;
        printf("Find max diff elements with repeating elements: ");
        find_two_el_with_max_diff(a, a_end, &max_diff_el, &pre_max_diff_el, mu1);
        if (fabs(max_diff_el - expected_max_diff_el) > EPS || fabs(pre_max_diff_el - expected_pre_max_diff_el) > EPS)
            printf("FAIL\n");
        else
            printf("OK\n");
        free(a);
    }

    return SUCCESS;
}

int test_if_delete(void)
{
    printf("\nDelete elements with max diff:");
    {
        double test[] = { 1, 2, 1, 3, 3, 2, 4, 5 };

        double *a;
        int n = 8;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double mu1 = 3.573529;
        int expected_n = 6;
        printf("Delete several reapiting elements with max diff: ");
        if_delete(&a, &a_end, mu1);
        if (a_end - a == expected_n)
            printf("Ok\n");
        else
            printf("FAIL\n");
        free(a);
    }
    {
        double test[] = { 1, 2, 3, 3, 4, 5 };
        double *a;
        int n = 6;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double mu1 = 4;
        int expected_n = 4;
        printf("Delete two elements with max diff: ");
        if_delete(&a, &a_end, mu1);
        if (a_end - a == expected_n)
            printf("Ok\n");
        else
            printf("FAIL\n");
        free(a);
    }
    //11
    {
        double test[] = { 1, 1, 1, 1, 1, 1 };
        double *a;
        int n = 6;
        a = malloc(n * sizeof(double));

        if (a == NULL)
        {
            printf("Allocation error.");
            return ERROR_ALLOCATION;
        }
        double *a_end = a + n;
        int i = 0;
        for (double *p = a; p < a_end; p++)
        {
            *p = test[i];
            i++;
        }
        double mu1 = 1;
        int expected_n = 4;
        printf("Delete two elements with max diff: ");
        if_delete(&a, &a_end, mu1);
        if (a_end - a == expected_n)
            printf("Ok\n");
        else
            printf("FAIL\n");
        free(a);
    }
    return SUCCESS;
}

int main(void)
{
    //TestCreate();
    test_delete();
    test_resize();
    test_if_insert();
    test_count_mu1();
    test_count_mu2();
    test_find_two_el_with_max_diff();
    test_if_delete();
    return 0;
}
