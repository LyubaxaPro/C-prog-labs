#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"

extern int errno;

int is_simple(const int num)
{
    if (num == 2)
        return TRUE;
    for (int i = 2; i <= sqrt(num); i++)
    {
        if (num % i == 0)
        {
            return FALSE;
        }
    }
    return TRUE;
}

void check_list_for_delete(digit *const d)
{
    if (d == NULL)
        return;
    delete(d);
    return;
}

void push(const int num, const int degree, digit *const d)
{
    if (num <= 0)
    {
        errno = CORRECT_ERROR;
        return;
    }

    node *temp_ptr = malloc(sizeof(struct node));
    if (temp_ptr == NULL)
    {
        errno = MALLOC_ERROR;
        return;
    }

    temp_ptr->num = num;
    temp_ptr->degree = degree;
    temp_ptr->p_next = NULL;

    if (d->head == NULL)
    {
        d->head = temp_ptr;
        d->tail = temp_ptr;
    }
    else
    {
        d->tail->p_next = temp_ptr;
        d->tail = d->tail->p_next;
    }
}

void pop_back(digit *const d, int *const num, int *const degree)
{
    node *prev_ptr = d->head;
    if (prev_ptr == NULL)
    {
        errno = EMPTY_LIST;
        return;
    }
    node *next_ptr = prev_ptr->p_next;
    if (next_ptr == NULL)
    {
        *num = prev_ptr->num;
        *degree = prev_ptr->degree;
        free(prev_ptr);
        d->head = NULL;
        d->tail = NULL;
        return;
    }
    while (next_ptr->p_next != NULL)
    {
        prev_ptr = next_ptr;
        next_ptr = next_ptr->p_next;
    }
    *num = next_ptr->num;
    *degree = next_ptr->degree;
    d->tail = prev_ptr;
    d->tail->p_next = NULL;
}

void make_list(int num, digit *const cur_list)
{
    if (num <= 0)
    {
        errno = CORRECT_ERROR;
        return;
    }
    cur_list->head = NULL;
    cur_list->tail = NULL;
    push(1, 1, cur_list);
    if (num == 1)
        return;

    int temp_divider = 2;
    int cur_degree;
    while (num != 1)
    {
        if (is_simple(temp_divider))
        {
            cur_degree = 0;
            while (num % temp_divider == 0 && num != 1)
            {
                cur_degree++;
                num = num / temp_divider;
            }
            push(temp_divider, cur_degree, cur_list);
        }
        temp_divider++;
    }
}

void print(const int cur_num, const int cur_degree)
{
    if (cur_num == 1)
    {
        printf("%d", cur_num);
        return;
    }

    if (cur_degree == 0)
        return;

    printf("%d %d ", cur_num, cur_degree);
}

void output(digit *const d)
{
    int cur_num = 0;
    int cur_degree;
    int prev_num = 0;
    while (cur_num != 1)
    {
        node *prev_ptr = d->head;
        if (prev_ptr == NULL)
        {
            return;
        }

        node *next_ptr = prev_ptr->p_next;
        if (next_ptr == NULL)
        {
            cur_num = prev_ptr->num;
            cur_degree = prev_ptr->degree;
            print(cur_num, cur_degree);
            return;
        }

        while (next_ptr->p_next != NULL)
        {
            if (next_ptr->p_next != NULL && next_ptr->num == prev_num)
                break;
            prev_ptr = next_ptr;
            next_ptr = next_ptr->p_next;
        }
        if (prev_num == 0)
        {
            cur_num = next_ptr->num;
            cur_degree = next_ptr->degree;
        }
        else
        {
            cur_num = prev_ptr->num;
            cur_degree = prev_ptr->degree;
        }
        prev_num = cur_num;
        print(cur_num, cur_degree);
    }
}

void delete(digit *const d)
{
    node *temp_ptr;
    node *next_ptr = d->head;
    while (next_ptr != NULL)
    {
        temp_ptr = next_ptr;
        next_ptr = next_ptr->p_next;
        free(temp_ptr);
    }
}


void input(digit *const d)
{
    int num = 0;
    int rc = scanf("%d", &num);
    if (num <= 0 || rc != TRUE)
    {
        errno = CORRECT_ERROR;
        return;
    }
    make_list(num, d);
}