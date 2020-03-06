#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "cdio.h"
#include "errors_processing.h"
#include "check_functions.h"
#include "memory_functions.h"
#include "test_memory_functions.h"
extern int errno;

void r4e_x_c9t_correct()
{
    printf("Resize buffer: ");
    errno = SUCCESS;
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    resize_x_coefficient(&students);
    ERRNO_ALLOCATION_CHECK;
    if (students.buffer_size == START_BUFFER_SIZE * COEFFICIENT)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void create_char_arr_right_size()
{
    errno = SUCCESS;
    printf("Create char arr with right size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, 10);
    if (errno == SUCCESS)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].surname);
    delete(&students);
}


void create_char_arr_wrong_size()
{
    errno = SUCCESS;
    printf("Create char arr with wrong size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_char_arr(&students.arr[0].surname, -10);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void create_double_arr_right_size()
{
    errno = SUCCESS;
    printf("Create double arr with right size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_double_arr(&students.arr[0].marks, 10);
    if (errno == SUCCESS)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(students.arr[0].marks);
    delete(&students);
}


void create_double_arr_wrong_size()
{
    errno = SUCCESS;
    printf("Create double arr with wrong size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;

    create_double_arr(&students.arr[0].marks, -10);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void reduce_student_correct_size()
{
    errno = SUCCESS;
    printf("Reduce correct size array: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;
    for (int i = 0; i < START_BUFFER_SIZE; i++)
    {
        create_char_arr(&students.arr[i].group, strlen("IUIU") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].group, "IUIU");

        create_char_arr(&students.arr[i].surname, strlen("Iasa") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].surname, "Iasa");

        create_char_arr(&students.arr[i].dob, DOB_SIZE + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].dob, "1999.09.09");

        students.arr[i].marks_size = 4;
        create_double_arr(&students.arr[i].marks, 4);
        for (int k = 0; k < 4; k++)
            students.arr[i].marks[k] = k;
        students.arr[i].mid_mark = 0;
        students.cur_size++;
    }

    reduce_student(&students, 2);
    if (errno == SUCCESS && students.cur_size == 3)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);  
}

void reduce_student_negative_size()
{
    errno = SUCCESS;
    printf("Reduce negative size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;
    for (int i = 0; i < START_BUFFER_SIZE; i++)
    {
        create_char_arr(&students.arr[i].group, strlen("IU7a") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].group, "IU7a");

        create_char_arr(&students.arr[i].surname, strlen("Iasa") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].surname, "Iasa");

        create_char_arr(&students.arr[i].dob, DOB_SIZE + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].dob, "1999.09.09");

        students.arr[i].marks_size = 4;
        create_double_arr(&students.arr[i].marks, 4);
        for (int k = 0; k < 4; k++)
            students.arr[i].marks[k] = k;
        students.arr[i].mid_mark = 0;
        students.cur_size++;
    }

    reduce_student(&students, -2);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);  
}

void reduce_student_much_size()
{
    errno = SUCCESS;
    printf("Reduce too much size: ");
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    ERRNO_ALLOCATION_CHECK;
    for (int i = 0; i < START_BUFFER_SIZE; i++)
    {
        create_char_arr(&students.arr[i].group, strlen("IU7a") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].group, "IU7a");

        create_char_arr(&students.arr[i].surname, strlen("Iasa") + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].surname, "Iasa");

        create_char_arr(&students.arr[i].dob, DOB_SIZE + 1);
        ERRNO_ALLOCATION_CHECK;
        strcpy(students.arr[i].dob, "1999.09.09");

        students.arr[i].marks_size = 4;
        create_double_arr(&students.arr[i].marks, 4);
        for (int k = 0; k < 4; k++)
            students.arr[i].marks[k] = k;
        students.arr[i].mid_mark = 0;
        students.cur_size++;
    }

    reduce_student(&students, 23);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);  
}


void r4e_d4e_arr_correct_size()
{
    errno = SUCCESS;
    printf("Reduce correct size double array: ");
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
        students.arr[0].marks[k] = k % 5;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    reduce_double_arr(&students.arr[0].marks, 5, &students.arr[0].marks_size);
    if (errno == SUCCESS && students.arr[0].marks_size == 3)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void r4e_d4e_arr_not_correct_size()
{
    errno = SUCCESS;
    printf("Reduce not correct size double array: ");
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
        students.arr[0].marks[k] = k % 5;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    reduce_double_arr(&students.arr[0].marks, -3, &students.arr[0].marks_size);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void r4e_d4e_arr_null_size()
{
    errno = SUCCESS;
    printf("Reduce null size double array: ");
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
        students.arr[0].marks[k] = k % 5;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    reduce_double_arr(&students.arr[0].marks, 0, &students.arr[0].marks_size);
    if (errno == SUCCESS)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void r4e_d4e_arr_too_much_size()
{
    errno = SUCCESS;
    printf("Reduce too much size double array: ");
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
        students.arr[0].marks[k] = k % 5;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    reduce_double_arr(&students.arr[0].marks, 20, &students.arr[0].marks_size);
    if (errno == NOT_CORRECT_SIZE_OF_VAL)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}

void r4e_d4e_arr_same_size()
{
    errno = SUCCESS;
    printf("Reduce same size double array: ");
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
        students.arr[0].marks[k] = k % 5;
    students.arr[0].mid_mark = 0;
    students.arr[0].marks_size = 8;
    students.cur_size++;

    reduce_double_arr(&students.arr[0].marks, 8, &students.arr[0].marks_size);
    if (errno == EMPTY_AFTER_ACT)
        printf("OK\n");
    else
        printf("FAIL\n");
    delete(&students);
}