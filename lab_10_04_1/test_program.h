#ifndef TEST_PROGRAM_H
#define TEST_PROGRAM_H
#include "structs.h"

void fill_array(students_t *const students, char const *const group, 
char const *const surname, char const *const dob, const int marks_size,
const int mark, const int arr_size);
void test_d4e_older_17_null();
void test_delete_older_17_all_e6t();
void test_delete_older_17_one_e6t();
void del_all_marks_less_4();
void del_null_marks_less_4();
void del_correct_marks_less_4();
#endif