#ifndef CHECK_FUNCTIONS_H
#define CHECK_FUNCTIONS_H
#include "structs.h"
void check_group(char const *const string);
void check_surname(char const *const string);
void parse_dob(char const *const string, int *year, int *month, int *day);
void check_dob(char const *const string);
int check_age_for_delete(student_t const *const student);
#endif 