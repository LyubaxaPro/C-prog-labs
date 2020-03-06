#ifndef BASE_FUNCTIONS_H
#define BASE_FUNCTIONS_H

#include "structs.h"
void push(const int num, const int degree, digit *const d);
void pop_back(digit *const d, int *const num, int *const degree);
void make_list(int num, digit *const cur_list);
void print(const int cur_num, const int cur_degree);
void output(digit *const d);
void delete(digit *const d);
void input(digit *const d);
int is_simple(const int num);
void check_list_for_delete(digit *const d);
#endif