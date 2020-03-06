#include "stdio.h"
#include "test.h"
#include "function.h"
#include <assert.h>
#include <string.h>


#define DEBUG_OUT     printf("\nDefault: [%s]"  \
           "\n     My: [%s]"                    \
           "\nNumer: default:[%d] my:[%d]", default_buf, my_buf, dflt_ans, my_ans); \

#define TEST_OK printf(" \x1b[37;42m OK \x1b[0m");
#define TEST_FAILED                         \
{                                           \
    printf(" \x1b[37;41m FAILED \x1b[0m");  \
    DEBUG_OUT                               \
    return;                                 \
}



void test_d_1()
{
    const int buf_size = 100;
    printf("\n=== Test [d] 1 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 0, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, buf_size, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, buf_size, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_d_2()
{
    const int buf_size = 10;
    printf("\n=== Test [d] 2 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 0, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, buf_size * 0, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, buf_size * 0, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_d_3()
{
    const int printf_buf = 1;
    printf("\n=== Test [d] 3 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 1, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, printf_buf, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, printf_buf, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}


void test_i_1()
{
    const int buf_size = 100;
    printf("\n=== Test [i] 1 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 1, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, buf_size, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, buf_size, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_i_2()
{
    printf("\n=== Test [i] 2 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 1, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, 0, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, 0, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_i_3()
{
    const int printf_buf = 10;
    printf("\n=== Test [i] 3 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 1, b = 12, c = 1234, d = -123456, e = -1, f = -111111111;
    int dflt_ans = snprintf(default_buf, printf_buf, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, printf_buf, "(%i)(%i)(%i)(%i)(%i)(%i)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}



void test_hi_1()
{
    const int buf_size = 100;
    printf("\n=== Test [hi] 1 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const short int a = 1, b = 12, c = 1234, d = -12, e = -1, f = -111;
    int dflt_ans = snprintf(default_buf, buf_size, "(%hi)(%hi)(%hi)(%hi)(%hi)(%hi)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, buf_size, "(%hi)(%hi)(%hi)(%hi)(%hi)(%hi)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_hi_2()
{
    const int buf_size = 100;
    printf("\n=== Test [hi] 2 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const short int a = 1, b = 12, c = 1234, d = -12, e = -1, f = -111;
    int dflt_ans = snprintf(default_buf, buf_size * 0, "(%hi)(%hi)(%hi)(%hi)(%hi)(%hi)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, buf_size * 0, "(%hi)(%hi)(%hi)(%hi)(%hi)(%i)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_hi_3()
{
    const int printf_buf = 10;
    printf("\n=== Test [hi] 3 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const short int a = 1, b = 12, c = 1234, d = -12, e = -1, f = -111;
    int dflt_ans = snprintf(default_buf, printf_buf, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);
    int my_ans = my_snprintf(my_buf, printf_buf, "(%d)(%d)(%d)(%d)(%d)(%d)", a, b, c, d, e, f);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_s_1()
{
    const int buf_size = 100;
    printf("\n=== Test [s] 1 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const char *s1 = "go ";
    const char *s2 = " stAdy ";
    const char *s3 = " C++ ";
    const char *s4 = " please!!! ";
    int dflt_ans = snprintf(default_buf, buf_size, "(%s)(%s)(%s)(%s)", s1, s2, s3, s4);
    int my_ans = my_snprintf(my_buf, buf_size, "(%s)(%s)(%s)(%s)", s1, s2, s3, s4);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_s_2()
{
    const int buf_size = 100;
    printf("\n=== Test [s] 2 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const char *s1 = "go ";
    const char *s2 = " stAdy ";
    const char *s3 = " C++ ";
    const char *s4 = " please!!! ";
    int dflt_ans = snprintf(default_buf, buf_size * 0, "( %s )( %s )( %s )( %s )", s1, s2, s3, s4);
    int my_ans = my_snprintf(my_buf, buf_size * 0, "( %s )( %s )( %s )( %s )", s1, s2, s3, s4);
    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_s_3()
{
    const int printf_buf = 5;
    printf("\n=== Test [s] 3 ===");
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const char *s1 = "go ";
    const char *s2 = " stAdy ";
    const char *s3 = " C++ ";
    const char *s4 = " please!!! ";
    int dflt_ans = snprintf(default_buf, printf_buf, "(%s)(%s)(%s)(%s)", s1, s2, s3, s4);
    int my_ans = my_snprintf(my_buf, printf_buf, "(%s)(%s)(%s)(%s)", s1, s2, s3, s4);
    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_all_1()
{
    printf("\n=== Test [all] 1 ===");
    const int buf_size = 100;
    char my_buf[] = "____________________________________________________________";
    char default_buf[] = "____________________________________________________________";
    const int a = 1, b = 12, c = 1234, d = -123456;
    const short sha = -1, shb = -2;
    const char *s = "c++ is better";
    int dflt_ans = snprintf(default_buf, buf_size, "(%i)(%hi)(%d)(%hd)(%i)(%d)(%s)", a, sha, b, shb, c, d, s);
    int my_ans = my_snprintf(my_buf, buf_size, "(%i)(%hi)(%d)(%hd)(%i)(%d)(%s)", a, sha, b, shb, c, d, s);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_all_3()
{
    printf("\n=== Test [all] 3 ===");
    const int buf_size = 100;
    const int printf_buf = 5;
    char my_buf[buf_size];
    char default_buf[buf_size];
    const int a = 1, b = 12, c = 1234, d = -123456;
    const short sha = -1, shb = -2;
    const char *s = "c++ is better";
    int dflt_ans = snprintf(default_buf, printf_buf, "(%i)(%hi)(%d)(%hd)(%i)(%d)(%s)", a, sha, b, shb, c, d, s);
    int my_ans = my_snprintf(my_buf, printf_buf, "(%i)(%hi)(%d)(%hd)(%i)(%d)(%s)", a, sha, b, shb, c, d, s);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}

void test_10()
{
    printf("\n=== Test 10 ===");
    const int buf_size = 5;
    char my_buf[] = "____";
    char default_buf[] = "____";
    const int c = 123456;
    int dflt_ans = snprintf(default_buf, buf_size, "((%d))", c);
    int my_ans = my_snprintf(my_buf, buf_size, "((%d))", c);

    if (dflt_ans != my_ans) TEST_FAILED
    if (strcmp(my_buf, default_buf) != 0) TEST_FAILED
    TEST_OK
}



int main()
{
    test_d_1();
    test_d_2();
    test_d_3();

    test_i_1();
    test_i_2();
    test_i_3();

    test_hi_1();
    test_hi_2();
    test_hi_3();

    test_s_1();
    test_s_2();
    test_s_3();

    test_all_1();
    test_all_3();

    test_10();

    printf("\n\n");
    return 0;
}
