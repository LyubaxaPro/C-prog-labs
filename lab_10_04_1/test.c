#include<stdio.h>
#include<stdlib.h>
#include "cdio.h"
#include "constants.h"
#include "errors_processing.h"
#include "program.h"
#include "structs.h"
#include "test_check_functions.h"
#include "test_memory_functions.h"
#include "test_compare_functions.h"
#include "test_program.h"


int main()
{
    printf("\nTest function check group\n");
    check_group_too_long_str();
    check_group_c5t_str();

    printf("\nTest function check surname\n");
    check_surname_too_long_str();
    check_surname_not_c5t_str();
    check_surname_c5t_str();

    printf("\nTest function parse dob\n");
    parse_correct_dob();

    printf("\nTest function check dob\n");
    check_correct_dob();
    check_dob_wrong_day();
    check_dob_wrong_month();
    check_dob_wrong_year();
    check_dob_wrong_symbols();
    check_dob_wrong_points();
    check_dob_too_long_str();
    check_dob_not_c5t_leap_year();
    check_dob_leap_year();

    printf("\nTest function check age for delete\n");
    check_age_for_del_correct();
    check_age_for_del_month();
    check_not_age_for_del();

    printf("\nTest function resize x coefficient\n");
    r4e_x_c9t_correct();

    printf("\nTest function create char arr\n");
    create_char_arr_right_size();
    create_char_arr_wrong_size();
    create_double_arr_right_size();
    create_double_arr_wrong_size();

    printf("\nTest function reduce student\n");
    reduce_student_much_size();
    reduce_student_negative_size();
    reduce_student_correct_size();

    printf("\nTest function reduce double arr\n");
    r4e_d4e_arr_correct_size();
    r4e_d4e_arr_correct_size();
    r4e_d4e_arr_same_size();
    r4e_d4e_arr_too_much_size();
    r4e_d4e_arr_null_size();
    r4e_d4e_arr_not_correct_size();

    printf("\nTest function count mid mark\n");
    count_mid_mark_correct();

    printf("\nTest function compare surname\n");
    compare_surname_same_str();
    compare_surname_f_subst_s();
    compare_surname_s_subst_f();
    compare_surname_diff_str();

    printf("\nTest function compare group\n");
    compare_group_diff_str();
    compare_group_s_subst_f();
    compare_group_f_subst_s();
    compare_group_s_subst_f();
    compare_group_diff_str();

    printf("\nTest function compare grade\n");
    compare_grade_f_bigger();
    compare_grade_s_bigger();

    printf("\nTest function delete older than 17\n");
    test_d4e_older_17_null();
    test_delete_older_17_all_e6t();
    test_delete_older_17_one_e6t();

    printf("\nTest function delete marks less 4\n");
    del_all_marks_less_4();
    del_null_marks_less_4();
    del_correct_marks_less_4();
}   