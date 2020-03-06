#include <stdio.h>
#include <stdlib.h>
#include "cdio.h"
#include "constants.h"
#include "errors_processing.h"
#include "program.h"
#include "structs.h"
#include "memory_functions.h"
#include "compare_functions.h"
#include "check_functions.h"
#include <stdarg.h>
extern int errno;

int main()
{
    students_t students;
    students.buffer_size = 0;
    students.cur_size = 0;

    create(&students);
    CREATE_ERROR;

    input(&students);
    PERROR(TRUE);

    delete_older_than_17(&students);
    PERROR(TRUE);

    delete_marks_less_4(&students);
    PERROR(TRUE);

    sort_by_field(&students);
    PERROR(TRUE);

    output(&students);
    delete(&students);
    return errno;
}
