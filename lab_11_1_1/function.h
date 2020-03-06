#ifndef FUNCTION_H
#define FUNCTION_H

int my_snprintf(char *buffer, int buf_size, const char *format, ...);
int calc_specs(const char *format);
void write_string_to_buffer(char *buffer, int *buf_ptr, char *str, int *need_write);
void write_int_to_buffer(char *buffer, int *buf_ptr, long long number, int *need_write);
void add_to_buffer(char *buffer, int *buf_ptr, char c, int *need_write);
int count_simbol(long long number);
int is_enabled_spec(char c);
int is_numeric_spec(char c);

#endif