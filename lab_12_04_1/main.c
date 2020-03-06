#include <string.h>
#include <stdio.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "base_functions.h"
#include "computation_functions.h"

int errno = SUCCESS;

int main()
{
    digit *default_ptr = NULL;
    char action[ACTION_LEN];
    scanf("%s", action);
    if (strcmp(action, "out") == SUCCESS)
    {
        digit out_d;

        input(&out_d);
        ERRNO_PROCESSING(default_ptr, default_ptr, default_ptr);

        output(&out_d);
        ERRNO_PROCESSING(&out_d, default_ptr, default_ptr);

        delete(&out_d);
        return SUCCESS;
    }

    if (strcmp(action, "mul") == SUCCESS)
    {
        digit d1, d2, result;

        input(&d1);
        ERRNO_PROCESSING(default_ptr, default_ptr, default_ptr);

        input(&d2);
        ERRNO_PROCESSING(&d1, default_ptr, default_ptr);

        multiplicate(&d1, &d2, &result);
        output(&result);

        delete(&d1);
        delete(&d2);
        delete(&result);
        return SUCCESS;
    }

    if (strcmp(action, "sqr") == SUCCESS)
    {
        digit d1, result;

        input(&d1);
        ERRNO_PROCESSING(default_ptr, default_ptr, default_ptr);

        multiplicate(&d1, &d1, &result);
        output(&result);

        delete(&d1);
        delete(&result);
        return SUCCESS;
    }

    if (strcmp(action, "div") == SUCCESS)
    {
        digit divident, divider, result;

        input(&divident);
        ERRNO_PROCESSING(default_ptr, default_ptr, default_ptr);

        input(&divider);
        ERRNO_PROCESSING(&divident, default_ptr, default_ptr);

        division(&divident, &divider, &result);
        ERRNO_PROCESSING(&divident, &divider, &result);

        output(&result);

        delete(&divident);
        delete(&divider);
        delete(&result);
        return SUCCESS;
    }

    errno = NOT_CORRECT_STR;
    ERRNO_PROCESSING(default_ptr, default_ptr, default_ptr);
}
