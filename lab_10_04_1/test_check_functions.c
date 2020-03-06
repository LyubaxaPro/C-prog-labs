#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "cdio.h"
#include "errors_processing.h"
#include "check_functions.h"
#include "memory_functions.h"
#include "test_check_functions.h"
extern int errno;

void check_group_too_long_str()
{
    printf("Too long string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE + 10];
    for (int i = 0; i < MAX_STR_SIZE + 5; i++)
    {
        string[i] = 'a';
    }
    string[MAX_STR_SIZE + 5] = '\0';
    check_group(string);
    ERRNO_COMPARE(TOO_LONG_STR);
}

void check_group_wrong_symbols()
{
    printf("Not correct symbols: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "IU1234+++=");
    check_group(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_group_c5t_str()
{
    printf("Correct string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "IU7-33B");
    check_group(string);
    ERRNO_COMPARE(SUCCESS);
}

void check_surname_too_long_str()
{
    printf("Too long string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE + 10];
    for (int i = 0; i < MAX_STR_SIZE + 5; i++)
    {
        string[i] = 'a';
    }
    string[MAX_STR_SIZE + 5] = '\0';
    check_surname(string);
    ERRNO_COMPARE(TOO_LONG_STR);
}

void check_surname_not_c5t_str()
{
    printf("Not correct string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];
    for (int i = 0; i < 10; i++)
    {
        string[i] = 'a';
    }
    string[10] = '!';
    string[11] = '\0';
    check_surname(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_surname_wrong_symbols()
{
    printf("Not correct symbols: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "Prohorova1234");
    check_surname(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_surname_c5t_str()
{
    printf("Correct string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "Prohorova");
    check_surname(string);
    ERRNO_COMPARE(SUCCESS);
}

void parse_correct_dob()
{
    printf("Correct dob: ");
    int year;
    int month;
    int day;
    errno = SUCCESS;
    char string[MAX_STR_SIZE + 10];
    strcpy(string, "1999.09.08");
    parse_dob(string, &year, &month, &day);
    if (year == 1999 && month == 9 && day == 8)
        printf("OK\n");
    else
        printf("FAIL\n");
}

void check_dob_too_long_str()
{
    printf("Too long string: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE + 10];
    for (int i = 0; i < MAX_STR_SIZE + 5; i++)
    {
        string[i] = '1';
    }
    string[MAX_STR_SIZE + 5] = '\0';
    check_dob(string);
    ERRNO_COMPARE(TOO_LONG_STR);
}

void check_dob_wrong_points()
{
    printf("Wrong place of points: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "09.09.1999");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_dob_wrong_symbols()
{
    printf("Wrong symbols: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "1999.Aa.12");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}


void check_dob_wrong_year()
{
    printf("Wrong year: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2030.01.12");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_dob_wrong_month()
{
    printf("Wrong month: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2000.31.12");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_dob_wrong_day()
{
    printf("Wrong day: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2000.01.87");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_correct_dob()
{
    printf("Correct dob: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2000.01.12");
    check_dob(string);
    ERRNO_COMPARE(SUCCESS);
}

void check_dob_leap_year()
{
    printf("Correct leap year: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2016.02.29");
    check_dob(string);
    ERRNO_COMPARE(SUCCESS);
}

void check_dob_not_c5t_leap_year()
{
    printf("Not correct leap year: ");
    errno = SUCCESS;
    char string[MAX_STR_SIZE];

    strcpy(string, "2015.02.29");
    check_dob(string);
    ERRNO_COMPARE(INPUT_ERROR);
}

void check_age_for_del_correct()
{
    printf("Correct age for delete: ");
    errno = SUCCESS;
    student_t data;
    create_char_arr(&data.dob, DOB_SIZE);
    char string[MAX_STR_SIZE];
    strcpy(string, "1980.02.01");
    for (int i = 0; i < strlen(string); i++)
        data.dob[i] = string[i];
    if (check_age_for_delete(&data) == TRUE)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(data.dob);
}

void check_not_age_for_del()
{
    printf("Not age for delete: ");
    errno = SUCCESS;
    student_t data;
    create_char_arr(&data.dob, DOB_SIZE);
    char string[MAX_STR_SIZE];
    strcpy(string, "2011.02.01");
    for (int i = 0; i < strlen(string); i++)
        data.dob[i] = string[i];
    if (check_age_for_delete(&data) == FALSE)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(data.dob);
}

void check_age_for_del_month()
{
    printf("Older for one month: ");
    errno = SUCCESS;
    student_t data;
    create_char_arr(&data.dob, DOB_SIZE);
    char string[MAX_STR_SIZE];
    strcpy(string, "2002.10.01");
    for (int i = 0; i < strlen(string); i++)
        data.dob[i] = string[i];
    if (check_age_for_delete(&data) == TRUE)
        printf("OK\n");
    else
        printf("FAIL\n");
    free(data.dob);
}