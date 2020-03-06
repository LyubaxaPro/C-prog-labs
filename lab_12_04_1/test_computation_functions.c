#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"
#include "computation_functions.h"
#include "test_computation_functions.h"

extern int errno;

int make_num(digit *const d)
{
    int result = 1;
//    int cur_num;
//    int cur_degree;
//    while (d->head != NULL)
//    {
//        pop_back(d, &cur_num, &cur_degree);
//        if (cur_num == 1)
//        {
//            break;
//        }

//        if (cur_degree == 0)
//        {
//            continue;
//        };
//        for (int i = 0; i < cur_degree; i++)
//        {
//            result *= cur_num;
//        }
//    }
    node *temp = d->head;
    while (temp != NULL)
    {
        for (int i = 0; i < temp->degree; i++)
            result *= temp->num;
        temp = temp->p_next;
    }
    return result;
}

void check_multiplicate(char const *const string_to_print, const int first_d,
const int second_d, const int expected_result)
{
    errno = SUCCESS;
    printf("%s", string_to_print);
    digit d1, d2, result;
    make_list(first_d, &d1);
    make_list(second_d, &d2);
    multiplicate(&d1, &d2, &result);
    MAKE_NUM_AND_ERRNO_CHECK(expected_result, SUCCESS, result);
    delete(&d1);
    delete(&d2);
    delete(&result);
} 


void check_multiplicate_one_size()
{
    check_multiplicate("Check function multiplicate with one size of list: ", 8, 2, 16);
} 

void check_multiplicate_f_l()
{
    check_multiplicate("Check function multiplicate first list is longer: ", 15, 2, 30);
}

void check_multiplicate_s_l()
{
    check_multiplicate("Check function multiplicate second list is longer: ", 2, 15, 30);
}

void check_rewrite_list()
{
    errno = SUCCESS;
    printf("Check function rewrite list: ");
    digit d1;
    make_list(14, &d1);
    rewrite_list(&d1, 27);
    MAKE_NUM_AND_ERRNO_CHECK(27, SUCCESS, d1);
    delete(&d1);
}

void test_check_div_zero_div()
{
    errno = SUCCESS;
    printf("Test function check division with zero in result: ");
    digit d1;
    d1.head = NULL;
    d1.tail = NULL;
    push(1, 1, &d1);
    push(2, -8, &d1);
    push(3, 1, &d1);

    check_division(&d1);
    TEST_ERRNO_CHECK(ZERO_DIVISION);
    delete(&d1);
}

void test_check_div_int_div()
{
    errno = SUCCESS;
    printf("Test function check division with not zero result: ");
    digit d1;
    d1.head = NULL;
    d1.tail = NULL;
    push(1, 1, &d1);
    push(2, 8, &d1);
    push(3, -1, &d1);

    check_division(&d1);
    MAKE_NUM_AND_ERRNO_CHECK(85, SUCCESS, d1);
    delete(&d1);
}

void check_division_zero()
{
    errno = SUCCESS;
    printf("Test function division with zero in result: ");
    digit d1, d2, result;
    make_list(12, &d1);
    make_list(35, &d2);
    division(&d1, &d2, &result);
    TEST_ERRNO_CHECK(ZERO_DIVISION);
    delete(&d1);
    delete(&d2);
    delete(&result);
}

void check_division_int()
{
    errno = SUCCESS;
    printf("Test function division with int in result: ");
    digit d1, d2, result;
    make_list(35, &d1);
    make_list(12, &d2);
    division(&d1, &d2, &result);
    MAKE_NUM_AND_ERRNO_CHECK(2, SUCCESS, result);
    delete(&d1);
    delete(&d2);
    delete(&result);
}








