/* Программа создаёт файл и заполняет его N случайными числами взятыми из интервала [0, 100].
   Сортировка выбором по возрастанию элементов.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ERROR_FILENAME 2
#define OK 0
#define N 20
#define SUCCESS 0
#define EMPTY_FILE 1
#define TRUE 1
#define FALSE 0

//По заданной позиции, позволяет прочитать число в указанной позиции
int get_number_by_pos(FILE *f, const int position)
{
    int number;
    fseek(f, position * sizeof(int) - sizeof(int), SEEK_SET);
    fread(&number, sizeof(int), 1, f);
    return number;
}

//По заданной позиции, позволяет записать число в указанную позицию
void put_number_by_pos(FILE *f, const int position, const int number)
{
    fseek(f, position * sizeof(int) - sizeof(int), SEEK_SET);
    fwrite(&number, sizeof(int), 1, f);
}

// Сортировка пузырьком с флагом. Если за один проход по всем элементам не сделанно ни одной перестановки, сортировка прекращается (т.к массив уже отсортирован).
int buble_sort(FILE *f)
{
    int temp_num;
    int prev_num;
    int is_not_ordered = TRUE;
    int temp_position;
    fseek(f, 0, SEEK_SET);

    while (is_not_ordered)
    {
        if (!fread(&temp_num, sizeof(int), 1, f))
        {
            return FALSE;
        }

        temp_position = 0;
        prev_num = temp_num;
        is_not_ordered = FALSE;

        while (fread(&temp_num, sizeof(int), 1, f) == TRUE)
        {
            temp_position += 1;
            temp_num = get_number_by_pos(f, temp_position);
            if (prev_num > temp_num)
            {
                put_number_by_pos(f, temp_position - 1, temp_num);
                put_number_by_pos(f, temp_position, prev_num);
                is_not_ordered = TRUE;
            }
            else
            {
                prev_num = temp_num;
            }
        }
        fseek(f, 0, SEEK_SET);
    }
    return TRUE;
}

//Создание файла с N случайными числами
void create_file(FILE *f)
{
    int temp_num;
    srand(time(NULL));
    for (int i = 0; i < N; i++)
    {
        temp_num = rand() % (100);  //  [0,100]
        fwrite(&temp_num, sizeof(int), 1, f);
    }
}

//Вывод содержимого файла на экран
int print_file(FILE *f)
{
    int temp_num;
    int count = 0;
    while (fread(&temp_num, sizeof(int), 1, f) == TRUE)
    {
        printf("%d ", temp_num);
        count += 1;
    }
    if (!count)
    {
        return FALSE;
    }
    return TRUE;
}

void usage(void)
{
    printf("app.exe <action>\n");
    printf("<action>\n");
    printf("\t c - create file \n");
    printf("\t p - print file \n");
    printf("\t o - put numbers in order\n");
}
int main(int argc, char *argv[])
{
    FILE *f;

    if (argc != 3)
    {
        usage();
        return ERROR_FILENAME;
    }

    if (strcmp(argv[1], "c") == OK)
    {
        if ((f = fopen(argv[2], "wb")) == NULL)
        {
            return ERROR_FILENAME;
        }
        create_file(f);
        fclose(f);
        return SUCCESS;
    }

    if (strcmp(argv[1], "p") == OK)
    {
        if ((f = fopen(argv[2], "rb")) == NULL)
        {
            return ERROR_FILENAME;
        }
        if (!print_file(f))
        {
            return EMPTY_FILE;
        }
        fclose(f);
        return SUCCESS;
    }

    if (strcmp(argv[1], "s") == OK)
    {
        if ((f = fopen(argv[2], "r + b")) == NULL)
        {
            return ERROR_FILENAME;
        }
        if (!buble_sort(f))
        {
            return EMPTY_FILE;
        }
        fclose(f);
        return SUCCESS;
    }

    usage();
    return ERROR_FILENAME;
}
