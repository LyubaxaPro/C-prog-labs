#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STR_SEPARATOR_SIZE 8
#define TRUE 1
#define FALSE 0
#define ONLY_DELIMETRS 2
#define SUCCESS 0
#define INPUT_ERROR 1
#define MAX_LENGTH 256
#define EMPTY 0


void swap(char **a, char **b)
{
    char *t = *a;
    *a = *b;
    *b = t;
}

int is_delimiter(const char c)
{
    const char str_separator[STR_SEPARATOR_SIZE] = { ' ', ',', ';', ':', '-', '.', '!', '?' };
    for (int i = 0; i < STR_SEPARATOR_SIZE; ++i)
    {
        if (c == str_separator[i])
        {
            return TRUE;
        }
    }
    return FALSE;
}

void read_str(char *const data, char **starts, int *const count_words)
{
    int position = 0;
    char c = getchar();

    int is_prev_sep = TRUE;
    while (c != '\n' && c != EOF)
    {
        data[position] = c;
        if (is_delimiter(c))
        {
            is_prev_sep = TRUE;
            data[position] = '\0';
        }
        else
        {
            if (is_prev_sep)
            {
                is_prev_sep = FALSE;
                starts[(*count_words)++] = &data[position];
            }
        }
        position++;
        c = getchar();
    }
    data[position] = '\0';
}

/*void make_unique(char **starts, int *const count_words)
{
    for (int i = 0; i < *count_words; ++i)
    {
        for (int j = i + 1; j < *count_words; ++j)
        {
            if (strcmp(starts[i], starts[j]) == 0)
            {
                swap(&starts[j], &starts[(*count_words) - 1]);
                (*count_words)--;
                j--;
            }
        }
    }
}*/

void make_unique(char **starts, int *const count_words)
{
    for (int i = 1; i < *count_words; i++)
    {
        if (strcmp(starts[i], starts[i - 1]) == 0)
        {
            if (i == *count_words - 1)
            {
                (*count_words)--;
            }
            else
            {
                for (int j = i; j < *count_words - 1; j++)
                {
                    starts[j] = starts[j + 1];
                }
                (*count_words)--;
                i--;
            }
        }
    }
}

/*void sort(char **starts, const int count_words)
{
    for (int i = 0; i < count_words; ++i)
    {
        for (int j = i + 1; j < count_words; ++j)
        {
            if (strcmp(starts[i], starts[j]) > 0)
            {
                swap(&starts[i], &starts[j]);
            }
        }
    }
}*/

void print_ans(char *const *starts, const int count_words)
{
    printf("Result:");
    for (int i = 0; i < count_words; ++i)
    {
        if (i != count_words - 1)
        {
            printf("%s ", starts[i]);
        }
        else
        {
            printf("%s", starts[i]);
        }
    }
}

int cmpstringp(const void *p1, const void *p2)
{
    return strcmp(* (char *const *) p1, * (char *const *) p2);
}

int main()
{
    char data[MAX_LENGTH + 1];
    char *starts[MAX_LENGTH];
    int count_words = 0;
    read_str(data, starts, &count_words);

    if (count_words == 0)
    {
        printf("Only delimeters.\n");
        return ONLY_DELIMETRS;
    }

    qsort(starts, count_words, sizeof(char *), cmpstringp);
    make_unique(starts, &count_words);
    if (count_words == 1)
    {
        printf("Not enough words.");
        return INPUT_ERROR;
    }
    print_ans(starts, count_words);
    return SUCCESS;
}
