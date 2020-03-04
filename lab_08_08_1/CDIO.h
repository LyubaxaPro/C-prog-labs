#ifndef __CDIO__H__
#define __CDIO__H__
#include "constants.h"

#ifndef __TYPEDEF__H__
#define __TYPEDEF__H__

typedef double *p_arr;

#endif

void create(double **arr, double **arr_end);
void input(p_arr arr, p_arr arr_end);
void output(p_arr const arr, p_arr const arr_end);
void delete(double **arr, double **arr_end, const int count_el_for_del);
#endif