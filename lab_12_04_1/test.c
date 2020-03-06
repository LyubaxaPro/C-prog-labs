#include <string.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"
#include "computation_functions.h"
#include "test_base_functions.h"
#include "test_computation_functions.h"

int errno = SUCCESS;

int main()
{
    printf("\nTest function is_simple\n");
    is_simple_test_simple();
    is_simple_test_not_simple();

    printf("\nTest function push\n");
    test_push_negativ_num();
    test_push_zero_num();
    test_push_correct_num();

    printf("\nTest function pop_back\n");
    test_function_pop_back_full();
    test_function_pop_back_empty();

    printf("\nTest function make_list correct n\n");
    make_list_correct_n();
    make_list_zero_n();
    make_list_negative_n();

    printf("\nTest function multiplicate\n");
    check_multiplicate_one_size();
    check_multiplicate_f_l();
    check_multiplicate_s_l();

    printf("\n");
    check_rewrite_list();

    printf("\nTest function check division\n");
    test_check_div_zero_div();
    test_check_div_int_div();

    printf("\nTest functoin division\n");
    check_division_int();
    check_division_zero();
}
