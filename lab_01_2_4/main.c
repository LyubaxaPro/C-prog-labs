//Программа предназначена для перевода заданного количества секунд в часы, минуты, секунды.

#include <stdio.h>

#define TIME_UNITS 60
#define END_WITH_SUCCESS 0

int main(void)
{
    int sec;
    int min, hours;

    printf("Введите секунды ");
    scanf("%d", &sec);

    hours = sec / TIME_UNITS / TIME_UNITS;
    min = sec / TIME_UNITS % TIME_UNITS;
    sec = sec % TIME_UNITS;

    printf("%d %d %d", hours, min, sec);

    return END_WITH_SUCCESS;
}