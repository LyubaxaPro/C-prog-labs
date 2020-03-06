#ifndef TEST_COMPUTATION_FUNCTIONS_H
#define TEST_COMPUTATION_FUNCTIONS_H
#include "structs.h"

void check_multiplicate_one_size();
int make_num(digit *const d);
void check_multiplicate_f_l();
void check_multiplicate_s_l();
void check_multiplicate(char const *const string_to_print, const int first_d,
const int second_d, const int expected_result);
void check_rewrite_list();
void test_check_div_zero_div();
void test_check_div_int_div();
void check_division_int();
void check_division_zero();



#endif
