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
#include "test_program.h"
#include "program.h"

extern int errno;

void fill_array(students_t *const students, char const *const group, 
char const *const surname, char const *const dob, const int marks_size, const int mark, const int arr_size)
{
    errno = SUCCESS;
    students->buffer_size = 0;
    students->cur_size = 0;

    create(students);
    ERRNO_ALLOCATION_CHECK;
    for (int i = 0; i < arr_size; i++)
    {
        create_char_arr(&students->arr[i].group, strlen(group) + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students->arr[i].group, group);

        create_char_arr(&students->arr[i].surname, strlen(surname) + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students->arr[i].surname, surname);

        create_char_arr(&students->arr[i].dob, DOB_SIZE + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students->arr[i].dob, dob);

        students->arr[i].marks_size = marks_size;
        create_double_arr(&students->arr[i].marks, marks_size);
        for (int k = 0; k < 4; k++)
            students->arr[i].marks[k] = mark;
        students->arr[i].mid_mark = 0;
        students->cur_size++;
    }
}

void test_d4e_older_17_null()
{
    printf("Test delete older than 17 all younger: ");
    students_t students;
    fill_array(&students, "ИУ7-31Б", "Iasa", "2012.09.09", 4, 5, START_BUFFER_SIZE);
    delete_older_than_17(&students);
    if (errno == SUCCESS && students.cur_size == START_BUFFER_SIZE)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void test_delete_older_17_all_e6t()
{
    errno = SUCCESS;
    printf("Test delete all elements: ");
    students_t students;
    fill_array(&students, "ИУ7-31Б", "Iasa", "1980.09.09", 4, 5, START_BUFFER_SIZE);

    delete_older_than_17(&students);
    if (students.cur_size == 0)
        ERRNO_COMPARE(EMPTY_AFTER_ACT)
    else
        printf("FAIL\n");
}

void test_delete_older_17_one_e6t()
{
    errno = SUCCESS;
    printf("Test delete older 17(1 element): ");
    students_t students;
    fill_array(&students, "ИУ7-31Б", "Iasa", "2005.09.09", 4, 5, START_BUFFER_SIZE);
    strcpy(students.arr[3].dob, "1980.09.09");
    delete_older_than_17(&students);
   // printf("%d\n", students.cur_size);
    if (students.cur_size == 3)
        ERRNO_COMPARE(SUCCESS)
    else
        printf("FAIL\n");
    delete(&students);
}

void del_all_marks_less_4()
{
    errno = SUCCESS;
    printf("Test delete all marks: ");
    students_t students;
    fill_array(&students, "ИУ7-31Б", "Iasa", "2005.09.09", 4, 1, START_BUFFER_SIZE);
    strcpy(students.arr[3].dob, "1980.09.09");
    delete_marks_less_4(&students);
    ERRNO_COMPARE(EMPTY_AFTER_ACT);
    delete(&students);
}

void del_null_marks_less_4()
{
    errno = SUCCESS;
    printf("Test delete null marks: ");
    students_t students;
    fill_array(&students, "ИУ7-31Б", "Iasa", "2005.09.09", 4, 5, 1);
    delete_marks_less_4(&students);
    if (students.arr[0].marks_size == 4)
        ERRNO_COMPARE(SUCCESS)
    else
        printf("FAIL\n");
    delete(&students);
}

void del_correct_marks_less_4()
{
    errno = SUCCESS;
    printf("Test delete correct size marks: ");
    students_t students;

    fill_array(&students, "ИУ7-31Б", "Iasa", "2005.09.09", 4, 5, 1);
    students.arr[0].marks[0] = 1;
    delete_marks_less_4(&students);
    if (students.arr[0].marks_size == 3)
        ERRNO_COMPARE(SUCCESS)
    else
        printf("FAIL\n");
    delete(&students);
}