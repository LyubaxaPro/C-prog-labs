#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct
{
    char *group;
    char *surname;
    char *dob;
    double *marks;
    double mid_mark;
    int marks_size;
} student_t;

typedef struct
{
    student_t *arr;
    int buffer_size;
    int cur_size;
}students_t;

#endif // STRUCTS_H

