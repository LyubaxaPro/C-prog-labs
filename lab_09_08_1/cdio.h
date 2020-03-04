#ifndef CDIO_H
#define CDIO_H
#include"structs.h"

void delete_matrix(matrix_t *const matrix_struct);
void input_matrix(matrix_t *const matrix_struct);
void output_matrix(matrix_t const *const matrix_struct);
void create_matrix(const int64_t rows, const int64_t columns, matrix_t *const temp_matrix);
#endif // CDIO_H
