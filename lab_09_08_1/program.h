#ifndef PROGRAM_H
#define PROGRAM_H
#include"structs.h"

void input_matrix_size(int64_t *const matrix_rows, int64_t *const matrix_columns);
void delete_column(matrix_t *const matrix_struct, const int64_t column);
void find_last_min_element(matrix_t const *const matrix_struct, int64_t *const row, int64_t *const column);
void delete_row(matrix_t *const matrix_struct, const int64_t row);
void make_square_matrix(matrix_t *const matrix_struct);
void resize_rows(matrix_t *const matrix_struct, const int64_t diff, const int row);
void resize_columns(matrix_t *const matrix_struct, const int64_t diff);
void add_rows(matrix_t *const matrix_struct, const int64_t count_rows_to_add);
void fill_row(matrix_t *const matrix_struct, const int64_t row_to_fill);
void add_columns(matrix_t *const matrix_struct, const int64_t count_columns_to_add);
void fill_columns(matrix_t *const matrix_struct, const int64_t column_to_fill);
void make_same_size(matrix_t *const matrix_a, matrix_t *const matrix_b);
void input_matrix_degree(int64_t *const matrix_a_degree, int64_t *const matrix_b_degree);
void matrix_in_degree(matrix_t *const matrix_struct, const int64_t degree);
void copy_matrix(matrix_t const *const matrix_from, matrix_t *const matrix_to);
void multiply_matrix(matrix_t const *const matrix_a, matrix_t const *const matrix_b, matrix_t *const matrix_result);
#endif // PROGRAM_H
