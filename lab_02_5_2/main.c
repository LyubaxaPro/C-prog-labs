#include <stdio.h>
#include <math.h>

#define END_WITH_SUCCESS 0
#define INPUT_ERROR 1
#define NOT_CORRECT_VAR 2

#define VAR_COUNT 8
#define ZERO 0
#define POSITIVE_SIGN 1
#define NEGATIVE_SIGN -1

#define EPS 1e-7


//Проверка знака векторного произведения
int sign_vect_pr(float ax, float ay, float bx, float by, float cx, float cy)
{
    float ans = (bx - ax) * (cy - ay) - (by - ay) * (cx - ax);
    if (ans > EPS)
        return POSITIVE_SIGN;
    if (ans < -EPS)
        return NEGATIVE_SIGN;
    return ZERO;
}

//Проверка пересечения
int intersec(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
{
    if ((x1 == x2 && y1 == y2) || (x3 == x4 && y3 == y4))
    {
        printf("Not a segment\n");
        return NOT_CORRECT_VAR;
    }

    int answer = (sign_vect_pr(x1, y1, x2, y2, x3, y3) * sign_vect_pr(x1, y1, x2, y2, x4, y4) < ZERO) &&
        (sign_vect_pr(x3, y3, x4, y4, x1, y1) * sign_vect_pr(x3, y3, x4, y4, x2, y2) < ZERO);
    printf("%d", answer);
    return END_WITH_SUCCESS;
}

int main(void)
{
    float x1, y1;
    float x2, y2;
    float x3, y3;
    float x4, y4;

    short rc = ZERO;
    rc += scanf("%f %f %f %f", &x1, &y1, &x2, &y2);
    rc += scanf("%f %f %f %f", &x3, &y3, &x4, &y4);

    if (rc != VAR_COUNT)
    {
        printf("Input error\n");
        return INPUT_ERROR;
    }

    return intersec(x1, y1, x2, y2, x3, y3, x4, y4);
}