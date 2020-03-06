#ifndef COMPUTATION_FUNCTIONS_H
#define COMPUTATION_FUNCTIONS_H

#include "structs.h"
void multiplicate(digit const *const d1, digit const *const d2, digit *const result);
void rewrite_list(digit *const d, int new_num);
void check_division(digit *const result);
void division(digit const *const divident, digit const *const divider, digit *const result);

#endif