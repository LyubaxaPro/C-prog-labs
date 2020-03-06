#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "function.h"

#define PARSE_ERROR 3
#define BUF_OVERFLOW 2
#define OK 0
#define NOT_ALL_SPECS_ADDED -1
#define BAD_SPECIFICATOR -2
#define ZERO_SIZE -3

int is_numeric_spec(char c)
{
    return c == 'd' || c == 'i';
}

int is_enabled_spec(char c)
{
    return c == 's' || is_numeric_spec(c);
}

int count_simbol(long long number)
{
    if (number == 0)
    {
        return 1;
    }
    int count = 0;
    while (number)
    {
        number /= 10;
        count++;
    }
    return count;
}

void add_to_buffer(char *buffer, int *buf_ptr, char c, int *need_write)
{
    if (*need_write)
        buffer[(*buf_ptr)] = c;
    if (*need_write > 0) 
        (*need_write)--;
    (*buf_ptr)++;
}

void write_int_to_buffer(char *buffer, int *buf_ptr, long long number, int *need_write)
{
    int number_len = count_simbol(number);
    if (number < 0)
    {
        add_to_buffer(buffer, buf_ptr, '-', need_write);
        number = -number;
    }
    for (int i = 0; i < number_len; ++i)
    {
        add_to_buffer(buffer, buf_ptr, number / pow(10., number_len - i - 1) + '0', need_write);
        number %= (int)pow(10, number_len - i - 1);
    }
}

void write_string_to_buffer(char *buffer, int *buf_ptr, char *str, int *need_write)
{
    int len = strlen(str);
    for (int i = 0; i < len; ++i)
    {
        add_to_buffer(buffer, buf_ptr, str[i], need_write);
    }
}

int calc_specs(const char *format)
{
    int format_size = strlen(format);
    int count_specs = 0;
    for (int i = 0; i < format_size; ++i)
    {
        if (format[i] == '%' && (i + 1 < format_size))
        {
            count_specs += (is_enabled_spec(format[i + 1]) ||
                (format[i + 1] == 'h' && i + 2 < format_size && is_numeric_spec(format[i + 2])));
        }
    }
    return count_specs;
}

int my_snprintf(char *buffer, int buf_size, const char *format, ...)
{
    int format_size = strlen(format);
    int count_specs_all = calc_specs(format);
    va_list arrays;
    va_start(arrays, format);
    int buf_ptr = 0;
    int need_write = buf_size;
    for (int i = 0; i < format_size; ++i)
    {
        if (format[i] == '%' && (i + 1 < format_size))
        {
            if (is_numeric_spec(format[i + 1]) || (format[i + 1] == 'h' && i + 2 < format_size && is_numeric_spec(format[i + 2])))
            {
                int number_to_write = va_arg(arrays, int);
                write_int_to_buffer(buffer, &buf_ptr, number_to_write, &need_write);
                i += 1 + (format[i + 1] == 'h');
                count_specs_all--;
                continue;
            }
            else
            {
                if (is_enabled_spec(format[i + 1]))
                {
                    char *str = va_arg(arrays, char*);
                    write_string_to_buffer(buffer, &buf_ptr, str, &need_write);
                    ++i;
                    count_specs_all--;
                    continue;
                }
                else
                {
                    return BAD_SPECIFICATOR;
                }
            }
        }
        add_to_buffer(buffer, &buf_ptr, format[i], &need_write);
    }
    va_end(arrays);
    if (count_specs_all)
    {
        return NOT_ALL_SPECS_ADDED;
    }
    if (buf_size > 0)
    {
        if (buf_ptr >= buf_size - 1)
        {
            buffer[buf_size - 1] = '\0';
        }
        else
        {
            buffer[buf_ptr] = '\0';
        }
    }

    return buf_ptr;
}