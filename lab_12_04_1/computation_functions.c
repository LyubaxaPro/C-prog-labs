#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"
#include "computation_functions.h"

extern int errno;

void multiplicate(digit const *const d1, digit const *const d2, digit *const result)
{
    node *temp_ptr1 = d1->head;
    node *temp_ptr2 = d2->head;
    result->head = NULL;
    result->tail = NULL;
    int temp_num;
    int temp_degree;

    while (temp_ptr1 != NULL && temp_ptr2 != NULL)
    {
        if (temp_ptr1->num == temp_ptr2->num)
        {
            temp_num = temp_ptr1->num;
            temp_degree = temp_ptr1->degree + temp_ptr2->degree;
            push(temp_num, temp_degree, result);
        }
        else
        {
            errno = ERROR_OF_LIST;
            return;
        }
        temp_ptr1 = temp_ptr1->p_next;
        temp_ptr2 = temp_ptr2->p_next;
    }
    if (temp_ptr1 == NULL && temp_ptr2 == NULL)
        return;

    if (temp_ptr2 != NULL)
        temp_ptr1 = temp_ptr2;

    while (temp_ptr1 != NULL)
    {
        push(temp_ptr1->num, temp_ptr1->degree, result);
        temp_ptr1 = temp_ptr1->p_next;
    }
}


void rewrite_list(digit *const d, int new_num)
{
    delete(d);
    make_list(new_num, d);
}

void check_division(digit *const result)
{
    int res = 1;
    node *temp_ptr = result->head;
    while (temp_ptr != NULL)
    {
        if (temp_ptr->degree > 0)
        {
            for (int i = 0; i < temp_ptr->degree; i++)
            {
                res *= temp_ptr->num;
            }
        }
        temp_ptr = temp_ptr->p_next;
    }

    temp_ptr = result->head;
    while (temp_ptr != NULL)
    {
        if (temp_ptr->degree < 0)
        {
            for (int i = 0; i < temp_ptr->degree * (-1); i++)
            {
                res /= temp_ptr->num;
                if (res < 1)
                {
                    errno = ZERO_DIVISION;
                    return;
                }
            }
        }
        temp_ptr = temp_ptr->p_next;
    }
    rewrite_list(result, res);
}


void division(digit const *const divident, digit const *const divider, digit *const result)
{
    node *temp_ptr1 = divident->head;
    node *temp_ptr2 = divider->head;
    result->head = NULL;
    int temp_num;
    int temp_degree;
    int flag_to_check = FALSE;

    while (temp_ptr1 != NULL && temp_ptr2 != NULL)
    {
        if (temp_ptr1->num == temp_ptr2->num)
        {
            temp_num = temp_ptr1->num;
            temp_degree = temp_ptr1->degree - temp_ptr2->degree;
            push(temp_num, temp_degree, result);
            if (temp_degree < 0)
                flag_to_check = TRUE;
        }
        else
        {
            errno = ERROR_OF_LIST;
            return;
        }
        temp_ptr1 = temp_ptr1->p_next;
        temp_ptr2 = temp_ptr2->p_next;
    }
    if (temp_ptr1 == NULL && temp_ptr2 == NULL)
    {
        if (flag_to_check == TRUE)
            check_division(result);
        return;
    }

    while (temp_ptr1 != NULL)
    {
        push(temp_ptr1->num, temp_ptr1->degree, result);
        temp_ptr1 = temp_ptr1->p_next;
    }
    while (temp_ptr2 != NULL)
    {
        push(temp_ptr2->num, temp_ptr2->degree * (-1), result);
        flag_to_check = TRUE;
        temp_ptr2 = temp_ptr2->p_next;
    }
    if (flag_to_check == TRUE)
        check_division(result);
}
