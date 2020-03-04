#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ERROR_FILENAME 1
#define ERROR_ARGS 53
#define OK 0
#define SUCCESS 0
#define ERROR_FILEDATA 2
#define TRUE 1
#define FALSE 0

#define MAX_SURNAME_LEN 26
#define MAX_NAME_LEN 11
#define NUMBER_OF_MARKS 4
#define ARRAY_LEN 300
#define EPS 0.000001


typedef struct
{
    char surname[MAX_SURNAME_LEN];
    char name[MAX_NAME_LEN];
    int marks[NUMBER_OF_MARKS];
}list_t;

void read_file(FILE *f, list_t list[], int *list_len)
{
    *list_len = 0;

    while (fgets(list[*list_len].surname, MAX_SURNAME_LEN, f) && list[*list_len].surname[0] != EOF)
    {
        if (!fgets(list[*list_len].name, MAX_NAME_LEN, f) || list[*list_len].name[0] == EOF)
        {
            return;
        }
        for (int i = 0; i < NUMBER_OF_MARKS; i++)
        {
            if (!(fscanf(f, "%d", &list[*list_len].marks[i]) == TRUE))
            {
                return;
            }
        }
        *list_len += 1;
        char s[3];
        fgets(s, 2, f);
    }
}

int sort(list_t list[], const int list_len)
{
    int j;
    list_t temp;
    for (int i = 1; i < list_len; i++)
    {
        temp = list[i];
        j = i;
        while (j > 0 && (strcmp(list[j - 1].surname, temp.surname) > 0))
        {
            list[j] = list[j - 1];
            j -= 1;
        }
        list[j] = temp;
    }
    for (int i = 1; i < list_len; i++)
    {
        if (strcmp(list[i].surname, list[i - 1].surname) == OK)
        {
            if (strcmp(list[i - 1].name, list[i].name) == OK)
            {
                return FALSE;
            }
            if (strcmp(list[i - 1].name, list[i].name) > 0)
            {
                temp = list[i];
                list[i] = list[i - 1];
                list[i - 1] = temp;
            }
        }
    }
    return TRUE;
}

void print_list(list_t list[], const int list_len)
{
    for (int i = 0; i < list_len; i++)
    {
        printf("%s", list[i].surname);
        printf("%s", list[i].name);
        for (int j = 0; j < NUMBER_OF_MARKS; j++)
        {
            printf("%d ", list[i].marks[j]);
        }
        printf("\n");
    }
}

void print_struct_to_file(list_t temp_struct, FILE* f)
{
    fprintf(f, "%s%s", temp_struct.surname, temp_struct.name);
    for (int j = 0; j < NUMBER_OF_MARKS; j++)
    {
        fprintf(f, "%d ", temp_struct.marks[j]);
    }
    fprintf(f, "\n");
}

int print_with_substr(char substr[], list_t list[], const int list_len, FILE* f)
{
    if (strlen(substr) == 0)
    {
        return FALSE;
    }
    char *istr;
    int count = 0;
    for (int i = 0; i < list_len; i++)
    {
        istr = strstr(list[i].surname, substr);
        if ((istr - list[i].surname) == 0)
        {
            print_struct_to_file(list[i], f);
            count += 1;
        }
    }
    if (!count)
    {
        return FALSE;
    }
    return TRUE;
}

void find_middle_mark(list_t list[], const int list_len, float mid_marks[])
{
    for (int i = 0; i < list_len; i++)
    {
        mid_marks[i] = 0;
        for (int j = 0; j < NUMBER_OF_MARKS; j++)
        {
            mid_marks[i] += list[i].marks[j];
        }
        mid_marks[i] /= 4;
    }
}

float find_mid(float mid_marks[], const int list_len)
{   
    float temp = 0.0;
    for (int i = 0; i < list_len; i++)
    {
        temp += mid_marks[i];
    }
    temp /= list_len;
    return temp;
}

void delete_structs(list_t list[], int *list_len, float mid_marks[], const float mid)
{
    int i = 0;
    while (i < *list_len)
    {
        if (mid - mid_marks[i] > EPS)
        {
            for (int j = i; j < *list_len - 1; j++)
            {
                mid_marks[j] = mid_marks[j + 1];
                list[j] = list[j + 1];
            }
            i -= 1;
            *list_len -= 1;
        }
        i += 1;
    }
}

void print_result(FILE* f, list_t list[], const int list_len)
{
    for (int i = 0; i < list_len; i++)
    {
        print_struct_to_file(list[i], f);
    }
}

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        return ERROR_ARGS;
    }
    
    // Сортирует по фамилии. Если фамили одинаковые - по имени.
    if ((strcmp(argv[1], "st") == OK) && (argc == 3))
    {
        FILE *f;

        if ((f = fopen(argv[2], "rt")) == NULL)
        {
            return ERROR_FILENAME;
        }

        list_t list[ARRAY_LEN];
        int list_len;

        read_file(f, list, &list_len);

        if (list_len == 0)
        {
            printf("Error file data.");
            fclose(f);
            return ERROR_FILEDATA;
        }

        if (!sort(list, list_len))
        {
            fclose(f);
            return ERROR_FILEDATA;
        }

        print_list(list, list_len);
        fclose(f);
        return SUCCESS;
    }

    //Выводит информацию о студентах, фамилия которых начинается с заданной подстроки, в другой файл. 
    if ((strcmp(argv[1], "ft") == OK) && (argc == 5))
    {
        FILE *f;

        if ((f = fopen(argv[2], "rt")) == NULL)
        {
            return ERROR_FILENAME;
        }

        list_t list[ARRAY_LEN];
        int list_len;

        read_file(f, list, &list_len);

        if (list_len == 0)
        {
            printf("Error file data.");
            fclose(f);
            return ERROR_FILEDATA;
        }

        fclose(f);

        if ((f = fopen(argv[3], "wt")) == NULL)
        {
            return ERROR_FILENAME;
        }

        if (!print_with_substr(argv[4], list, list_len, f))
        {
            fclose(f);
            return ERROR_ARGS;
        }

        fclose(f);
        return SUCCESS;
    }

    /*Для каждого студента вычисляет средний балл. Затем вычисляет среднее значение среднего балла и удаляет студентов, средний балл которых меньше среднего
      значения. Результат записывается в тот же файл. */

    if ((strcmp(argv[1], "dt") == OK) && (argc == 3))
    {
        FILE *f;
        if ((f = fopen(argv[2], "rt")) == NULL)
        {
            return ERROR_FILENAME;
        }

        list_t list[ARRAY_LEN];
        int list_len;

        read_file(f, list, &list_len);
        if (list_len == 0)
        {
            fclose(f);
            printf("Error file data.");
            return ERROR_FILEDATA;
        }

        fclose(f);

        float mid_marks[list_len];
        find_middle_mark(list, list_len, mid_marks);

        const float mid = find_mid(mid_marks, list_len);
        delete_structs(list, &list_len, mid_marks, mid);

        if (list_len == 0)
        {
            fclose(f);
            printf("Empty file.");
            return ERROR_FILEDATA;
        }

        f = fopen(argv[2], "wt");
        print_result(f, list, list_len);
        fclose(f);
        return SUCCESS;
    }

    printf("Error name of args.");
    return ERROR_ARGS;
}