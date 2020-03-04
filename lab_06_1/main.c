#include <stdio.h>
#include <string.h>


//Возвращает указатель на первое вхождение любого символа из второй строки в первую
const char *my_strpbrk(const char *str1, const char *str2)
{
    int i = 0;
    int j;
    if (str1 == NULL || str2 == NULL) 
    {
        return NULL;
    }

    while (str1[i] != '\0')
    {
        j = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
            {
                return (&str1[i]);
            }
            j += 1;
        }
        i += 1;
    }
    return NULL;
}

//Для строки str1 функция strspn() возвращает значение индекса первого символа из числа символов, входящих в строку str2.
int my_strspn(const char *str1, const char *str2)
{
    if (str1 == NULL || str2 == NULL) 
    {
        return 0;
    }

    int i = 0;
    int j;

    while (str1[i] != '\0')
    {
        j = 0;
        int c_in_str2 = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
            {
                c_in_str2 = 1;
                break;
            }
            j += 1;
        }
        if (!c_in_str2) 
        {
            return i;
        }
        i += 1;
    }
    return i;
}

//Определяет наибольшую длину начального участка строки, на которую указывает аргумент str1, не содержащего ни один из символов строки, на которую указывает аргумент str2.
int my_strcspn(const char *str1, const char *str2)
{
    int i = 0;
    int j;

    while (str1[i] != '\0')
    {
        j = 0;
        while (str2[j] != '\0')
        {
            if (str1[i] == str2[j])
            {
                return i;
            }
            j += 1;
        }
        i += 1;
    }
    return i;
}

//Функция strchr обнаруживает первое вхождение symb_code(преобразован в char) в строке,
// на которую указывает str. завершающий нулевой символ считается частью строки.
const char *my_strchr(const char *str, const int symb_code)
{
    if (str == NULL) 
    {
        return NULL;
    }

    int i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == (char) symb_code)
        {
            return &str[i];
        }
        i += 1;
    }
    if (str[i] == (char) symb_code)
    {
        return &str[i];
    }
    return NULL;
}

//Функция strrchr ищет последнее вхождения символа, код которого указан в аргументе symb_code, в строке, на которую указывает аргумент str.
const char *my_strrchr(const char *str, const int symb_code)
{
    if (str == NULL) 
    {
        return NULL;
    }

    int i = 0;
    int j = -1;
    while (str[i] != '\0')
    {
        if (str[i] == (char) symb_code)
        {
            j = i;
        }
        i += 1;
    }
    if (str[i] == (char) symb_code)
    {
        j = i;
    }
    if (j == -1)
    {
        return NULL;
    }
    else
    {
        return &str[j];
    }
}

int main(void)
{    
    char str1[] = "aaaa";
    char str2[] = "aba";

    // // Переменная, в которую будет занесен адрес первого найденного символа
    const char *isym;
    // //Поиск символов

    printf("Compare results for function strpbrk\n");
    printf("String1 = %s, string2 = %s\n", str1, str2);
    isym = strpbrk(str1, str2);
    printf("Result of function of string.h \t%s\n", isym);

    isym = my_strpbrk(str1, str2);
    printf("Result of my function \t\t%s\n", isym);
    printf("\n");

    int position;

    printf("Compare results for function strspn\n");
    printf("String1 = %s, string2 = %s\n", str1, str2);
    position = strspn(str1, str2);
    printf("Result of function of string.h \t%d\n", position);

    position = my_strspn(str1, str2);
    printf("Result of my function  \t\t%d\n", position);
    printf("\n");

    printf("Compare results for function strcspn\n");
    printf("String1 = %s, string2 = %s\n", str1, str2);
    position = strcspn(str1, str2);
    printf("Result of function of string.h \t%d\n", position);

    position = my_strcspn(str1, str2);
    printf("Result of my function  \t\t%d\n", position);
    printf("\n");

    char str [] = "1234";
    int symb_code = 49;  //Askii cod of 'l'
    printf("Compare results for function strchr\n");
    printf("String = %s, code of symbol = %d\n", str, symb_code);
    isym = strchr(str, symb_code);
    printf("Result of function of string.h \t%s\n", isym);

    isym = my_strchr(str, symb_code);
    printf("Result of my function  \t\t%s\n", isym);
    printf("\n");

    printf("Compare results for function strchr\n");
    printf("String = %s, code of symbol = %d\n", str, symb_code);
    isym = strrchr(str, symb_code);
    printf("Result of function of string.h \t%s\n", isym);

    isym = my_strrchr(str, symb_code);
    printf("Result of my function  \t\t%s\n", isym);
    printf("\n");
    
    return 0;
}