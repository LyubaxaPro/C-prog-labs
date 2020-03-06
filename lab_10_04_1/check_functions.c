#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "constants.h"
#include "structs.h"
#include "cdio.h"
#include "check_functions.h"
extern int errno;

void check_group(char const *const string)
{
    if (strlen(string) >= MAX_STR_SIZE)
    {
        errno = TOO_LONG_STR;
        return;
    }
}

void check_surname(char const *const string)
{
    int i = 0;
    if (strlen(string) >= MAX_STR_SIZE)
    {
        errno = TOO_LONG_STR;
        return;
    }
    while (string[i] != '\0')
    {
        if (!((string[i] >= 'a' && string[i] <= 'z') || (string[i] >= 'A' && string[i] <= 'Z')))
        {
            errno = INPUT_ERROR;
            return;
        }
        i++;
    }
}
void parse_dob(char const *const string, int *year, int *month, int *day)
{
    *year = 0;
    for (int i = 0; i < POINT_AFTER_YEAR; i++)
    {
        *year = *year * 10 + string[i] - '0';
    }

    *month = 0;
    for (int i = POINT_AFTER_YEAR + 1; i < POINT_AFTER_MONTH; i++)
        *month = *month * 10 + string[i] - '0';

    *day = 0;
    for (int i = POINT_AFTER_MONTH + 1; i < POINT_AFTER_DAY; i++)
        *day = *day * 10 + string[i] - '0';
}

void check_dob(char const *const string)
{
    int i = 0;
    if (strlen(string) != DOB_SIZE)
    {
        errno = TOO_LONG_STR;
        return;
    }
    while (string[i] != '\0')
    {
        if (i == 4 || i == 7)
        {
            if (string[i] != '.')
            {
                errno = INPUT_ERROR;
                return;
            }
        }
        else if (!(string[i] >= '0' && string[i] <= '9'))
        {
            errno = INPUT_ERROR;
            return;
        }
        i++;
    }
    int year;
    int month;
    int day;

    parse_dob(string, &year, &month, &day);

    if (year > CURRENT_YEAR || year <= 0)
    {
        errno = INPUT_ERROR;
        return;
    }

    if ((year == CURRENT_YEAR && month > CURRENT_MONTH) || month > DECEMBER || month <= 0)
    {
        errno = INPUT_ERROR;
        return;
    }

    if ((day > CURRENT_DAY && month == CURRENT_MONTH && year == CURRENT_YEAR) || (day <= 0))
    {
        errno = INPUT_ERROR;
        return;
    }

    if ((month == JANUARY || month == MARCH || month == MAY || month == JULY || month == AUGUST || month == OCTOBER || month == DECEMBER) && (day > 31))
    {
        errno = INPUT_ERROR;
        return;
    }
    if ((month == APRIL || month == JUNE || month == SEPTEMBER || month == NOVEMBER) && day > 30)
    {
        errno = INPUT_ERROR;
        return;
    }

    if (month == FEBRUARY)
    {
        if (((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) && day > 29)
        {
            errno = INPUT_ERROR;
            return;
        }
        if (!((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)) && day > 28)
        {
            errno = INPUT_ERROR;
            return;
        }
    }
}

int check_age_for_delete(student_t const *const student)
{
    int year;
    int month;
    int day;

    parse_dob(student->dob, &year, &month, &day);

    if ((CURRENT_YEAR - year) > AGE_FOR_DELETE)
    {
        return TRUE;
    }
    if ((CURRENT_YEAR - year) < AGE_FOR_DELETE)
        return FALSE;

    if (month < CURRENT_MONTH)
        return TRUE;
    if (month > CURRENT_MONTH)
        return FALSE;

    if (day >= CURRENT_DAY)
        return FALSE;

    return TRUE;
}