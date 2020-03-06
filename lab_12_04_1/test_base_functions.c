#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"
#include "test_base_functions.h"

extern int errno;

void is_simple_test_simple()
{
    printf("Test simple num: ");
    if (is_simple(5) == TRUE)
        printf("OK\n");
    else
        printf("FAIL\n");
}

void is_simple_test_not_simple()
{
    printf("Test simple num: ");
    if (is_simple(6) == FALSE)
        printf("OK\n");
    else
        printf("FAIL\n");
}

void test_push_negativ_num()
{
    errno = SUCCESS;
    printf("Test push num < 0: ");
    digit d;
    d.head = NULL;
    d.tail = NULL;
    push(-2, 3, &d);
    TEST_ERRNO_CHECK(CORRECT_ERROR)
}

void test_push_zero_num()
{
    errno = SUCCESS;
    printf("Test push num == 0: ");
    digit d;
    d.head = NULL;
    d.tail = NULL;
    push(0, 3, &d);
    TEST_ERRNO_CHECK(CORRECT_ERROR);
}

void test_push_correct_num()
{
    errno = SUCCESS;
    printf("Test push num > 0: ");
    digit d;
    d.head = NULL;
    d.tail = NULL;
    push(2, 3, &d);
    if (d.head->num == 2 && d.head->degree == 3)
    {
        TEST_ERRNO_CHECK(SUCCESS);
    }
    else
        printf("FAIL\n");
    delete(&d);
}

void test_function_pop_back_full()
{
    errno = SUCCESS;
    printf("Test pop_back from not empty list: ");
    digit d;
    d.head = NULL;
    d.tail = NULL;
    push(2, 3, &d);
    int num;
    int degree;
    pop_back(&d, &num, &degree);
    if (num == 2 && degree == 3)
    {
        TEST_ERRNO_CHECK(SUCCESS);
    }
    else
    {
        printf("FAIL\n");
        delete(&d);
    }
}

void test_function_pop_back_empty()
{
    errno = SUCCESS;
    printf("Test pop_back from empty list: ");
    digit d;
    d.head = NULL;
    d.tail = NULL;
    int num;
    int degree;
    pop_back(&d, &num, &degree);
    TEST_ERRNO_CHECK(EMPTY_LIST);
}

void make_list_negative_n()
{
    errno = SUCCESS;
    printf("Test make list from negative num: ");
    digit d;
    make_list(-2, &d);
    TEST_ERRNO_CHECK(CORRECT_ERROR);
}

void make_list_zero_n()
{
    errno = SUCCESS;
    printf("Test make list from zero num: ");
    digit d;
    make_list(0, &d);
    TEST_ERRNO_CHECK(CORRECT_ERROR);
}

void make_list_correct_n()
{
    errno = SUCCESS;
    printf("Test make list from correct num: ");
    digit d;
    make_list(121, &d);
    node *temp_ptr = d.head;
    while (temp_ptr != NULL)
    {
        if (temp_ptr->num == 1 && temp_ptr->degree == 1)
        {
            temp_ptr = temp_ptr->p_next;
            continue;
        }
        if (temp_ptr->num == 11 && temp_ptr->degree == 2)
        {
            temp_ptr = temp_ptr->p_next;
            continue;
        }
        if (temp_ptr->degree == 0)
        {
            temp_ptr = temp_ptr->p_next;
            continue;
        }
        printf("FAIL\n");
    }

    if (errno == SUCCESS)
        printf("OK\n");
    delete(&d);
}
