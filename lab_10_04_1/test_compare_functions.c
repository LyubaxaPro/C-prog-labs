#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "cdio.h"
#include "errors_processing.h"
#include "check_functions.h"
#include "compare_functions.h"
#include "memory_functions.h"
#include "test_compare_functions.h"
#include "program.h"
#include "math.h"
extern int errno;

void count_mid_mark_correct()
{
    errno = SUCCESS;
    printf("Count mid mark: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;
    create_char_arr(&students.arr[0].group, strlen("IU7a") + 1);
    ERRNO_ALLOCATION_CHECK;
    strcpy(students.arr[0].group, "IU7a");

    create_char_arr(&students.arr[0].surname, strlen("Iasa") + 1);
    ERRNO_ALLOCATION_CHECK;
    strcpy(students.arr[0].surname, "Iasa");

    create_char_arr(&students.arr[0].dob, DOB_SIZE + 1);
    ERRNO_ALLOCATION_CHECK;
    strcpy(students.arr[0].dob, "1999.09.09");

    students.arr[0].marks_size = 8;
    create_double_arr(&students.arr[0].marks, 8);
    for (int k = 0; k < 8; k++)
        students.arr[0].marks[k] = 1;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    double result = count_mid_mark(students.arr[0].marks, students.arr[0].marks_size);
    if (fabs(result - 1) < EPS)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void compare_surname_same_str()
{
    errno = SUCCESS;
    printf("Compare same str: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, strlen("Abcd") + 1);
    create_char_arr(&students.arr[1].surname, strlen("Abcd") + 1);

    strcpy(students.arr[0].surname, "Abcd");
    strcpy(students.arr[1].surname, "Abcd");
    if (compare_surname(&students.arr[0], &students.arr[1]) == EQUIVAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].surname);
    free(students.arr[1].surname);
    free(students.arr);
}

void compare_surname_f_subst_s()
{
    errno = SUCCESS;
    printf("Compare str first is substr second: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, strlen("Abcd") + 1);
    create_char_arr(&students.arr[1].surname, strlen("Abcdeee") + 1);

    strcpy(students.arr[0].surname, "Abcd");
    strcpy(students.arr[1].surname, "Abcdeee");
    if (compare_surname(&students.arr[0], &students.arr[1]) < 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].surname);
    free(students.arr[1].surname);
    free(students.arr);
}

void compare_surname_s_subst_f()
{
    errno = SUCCESS;
    printf("Compare str second is substr first: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, strlen("Abcdeee") + 1);
    create_char_arr(&students.arr[1].surname, strlen("Abcd") + 1);

    strcpy(students.arr[0].surname, "Abcdeee");
    strcpy(students.arr[1].surname, "Abcd");
    if (compare_surname(&students.arr[0], &students.arr[1]) > 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].surname);
    free(students.arr[1].surname);
    free(students.arr);
}

void compare_surname_diff_str()
{
    errno = SUCCESS;
    printf("Compare str diff size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, strlen("Abcd") + 1);
    create_char_arr(&students.arr[1].surname, strlen("Ioioooo") + 1);

    strcpy(students.arr[0].surname, "Abcd");
    strcpy(students.arr[1].surname, "Ioioooo");
    if (compare_surname(&students.arr[0], &students.arr[1]) < 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].surname);
    free(students.arr[1].surname);
    free(students.arr);
}

void compare_group_same_str()
{
    errno = SUCCESS;
    printf("Compare same str: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].group, strlen("IU7-33B") + 1);
    create_char_arr(&students.arr[1].group, strlen("IU7-33B") + 1);

    strcpy(students.arr[0].group, "IU7-33B");
    strcpy(students.arr[1].group, "IU7-33B");
    if (compare_group(&students.arr[0], &students.arr[1]) == EQUIVAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].group);
    free(students.arr[1].group);
    free(students.arr);
}

void compare_group_f_subst_s()
{
    errno = SUCCESS;
    printf("Compare str first is substr second: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].group, strlen("IU7") + 1);
    create_char_arr(&students.arr[1].group, strlen("IU7-33B") + 1);

    strcpy(students.arr[0].group, "IU7");
    strcpy(students.arr[1].group, "IU7-33B");
    if (compare_group(&students.arr[0], &students.arr[1]) < 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].group);
    free(students.arr[1].group);
    free(students.arr);
}


void compare_group_s_subst_f()
{
    errno = SUCCESS;
    printf("Compare str second is substr first: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].group, strlen("IU7-33B") + 1);
    create_char_arr(&students.arr[1].group, strlen("IU7") + 1);

    strcpy(students.arr[0].group, "IU7-33B");
    strcpy(students.arr[1].group, "IU7");
    if (compare_group(&students.arr[0], &students.arr[1]) > 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].group);
    free(students.arr[1].group);
    free(students.arr);
}

void compare_group_diff_str()
{
    errno = SUCCESS;
    printf("Compare str diff size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].group, strlen("Abcd") + 1);
    create_char_arr(&students.arr[1].group, strlen("Ioioooo") + 1);

    strcpy(students.arr[0].group, "Abcd");
    strcpy(students.arr[1].group, "Ioioooo");
    if (compare_group(&students.arr[0], &students.arr[1]) < 0)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].group);
    free(students.arr[1].group);
    free(students.arr);
}

void compare_grade_f_bigger()
{
    errno = SUCCESS;
    printf("Compare first > second: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_double_arr(&students.arr[0].marks, 5);
    create_double_arr(&students.arr[1].marks, 5);   
    students.arr[0].marks_size = 5;
    students.arr[1].marks_size = 5;
    for (int i = 0; i < 5; i++)
    {
        students.arr[0].marks[i] = 5;
        students.arr[1].marks[i] = 1;
    }

    students.arr[0].mid_mark = count_mid_mark(students.arr[0].marks, 5);
    students.arr[1].mid_mark = count_mid_mark(students.arr[1].marks, 5);

    if (compare_grade(&students.arr[0], &students.arr[1]) == FIRST_MORE)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].marks);
    free(students.arr[1].marks);
    free(students.arr);
}

void compare_grade_s_bigger()
{
    errno = SUCCESS;
    printf("Compare second > first: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_double_arr(&students.arr[0].marks, 5);
    create_double_arr(&students.arr[1].marks, 5);   
    students.arr[0].marks_size = 5;
    students.arr[1].marks_size = 5;
    for (int i = 0; i < 5; i++)
    {
        students.arr[0].marks[i] = 1;
        students.arr[1].marks[i] = 4;
    }

    students.arr[0].mid_mark = count_mid_mark(students.arr[0].marks, 5);
    students.arr[1].mid_mark = count_mid_mark(students.arr[1].marks, 5);

    if (compare_grade(&students.arr[0], &students.arr[1]) == FIRST_LESS)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].marks);
    free(students.arr[1].marks);
    free(students.arr);
}