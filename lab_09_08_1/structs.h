#ifndef STRUCTS_H
#define STRUCTS_H
#include<inttypes.h>

typedef struct
{
    int64_t rows; // кол-во строк матрицы
    int64_t columns; // кол-во столбцов матрицы
    int64_t **matrix; // массив указателей на строки матрицы
} matrix_t;

#endif // STRUCTS_H
