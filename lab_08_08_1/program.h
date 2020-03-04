#ifndef __PROGRAM__H__
#define __PROGRAM__H__
#include "constants.h"

#ifndef __TYPEDEF__H__
#define __TYPEDEF__H__

typedef double *p_arr;

#endif

void swap(p_arr a, p_arr b);
void resize_arr(p_arr *arr, p_arr *arr_end, const int diff_size);
void if_insert(p_arr *arr, p_arr *arr_end, const int position, const double mu2);
void input_p(int *const p);
double count_mu1(p_arr const arr, p_arr const arr_end);
double count_diff(const double arr_elem, const double elem_to_diff);
double count_mu2(p_arr const arr, p_arr const arr_end);
void find_two_el_with_max_diff(p_arr const arr, p_arr const arr_end, double *major, double *pre_major, const double mu1);
void if_delete(p_arr *arr, p_arr *arr_end, const double mu1);

#endif