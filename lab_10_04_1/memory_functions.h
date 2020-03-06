#ifndef MEMORY_FUNCTIONS_H
#define MEMORY_FUNCTIONS_H
#include "structs.h"
void resize_x_coefficient(students_t *const students);
void create_char_arr(char **arr, const int size);
void create_double_arr(double **arr, const int size);
void free_arrays(int n, ...);
void reduce_double_arr(double **arr, const int diff, int *marks_size);
void reduce_student(students_t *const data, const int index);
#endif