//Программа предназначена для нахождения периметра треугольника по заданным координатам трёх вершин.

#include <math.h>
#include <stdio.h>

#define END_WITH_SUCCESS 0

int main(void)
{
    float xa, ya;
    float xb, yb;
    float xc, yc;
    float ab, ac, bc;
    float p;

    printf("Введите координаты первой точки\n");
    scanf("%f %f", &xa, &ya);

    printf("Введите координаты второй точки\n");
    scanf("%f %f", &xb, &yb);

    printf("Введите координаты третьей точки\n");
    scanf("%f %f", &xc, &yc);


    ab = sqrt((xa - xb) * (xa - xb) + (ya - yb) * (ya - yb));
    bc = sqrt((xb - xc) * (xb - xc) + (yb - yc) * (yb - yc));
    ac = sqrt((xa - xc) * (xa - xc) + (ya - yc) * (ya - yc));

    p = ab + ac + bc;

    printf("%.5f", p);

    return END_WITH_SUCCESS;
}
