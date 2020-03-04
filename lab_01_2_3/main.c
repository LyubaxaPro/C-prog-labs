//Программа предназначена для рассчёта сопротивления трёх резиторов, соединённых параллельно.

#include <stdio.h>
#include <math.h>

#define END_WITH_SUCCESS 0

int main(void)
{
    float r1, r2, r3;
    float result;

    printf("Введите сопротивления резисторов ");
    scanf("%f %f %f", &r1, &r2, &r3);

    result = 1 / (1 / r1 + 1 / r2 + 1 / r3);

    printf("%.5f", result);
    
    return END_WITH_SUCCESS;
}
