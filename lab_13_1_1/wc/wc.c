//wc - print the number of lines, words, and bytes in files
#include "wc.h"

int iswnbspace (wint_t wc)
{
    return (wc == 0x00A0 || wc == 0x2007 || wc == 0x202F || wc == 0x2060);
}

int isnbspace (int c)
{
    return iswnbspace (btowc (c));
}

void write_counts (long long lines, long long words, long long chars,
    long long bytes, long long linelength, const char *file)
{
    if (print_lines)
        printf("%lld ", lines);

    if (print_words)
        printf("%lld ", words);

    if (print_chars)
        printf("%lld ", chars);

    if (print_bytes)
        printf("%lld ", bytes);

    if (print_linelength)
        printf("%lld ", linelength);

    if (file)
        printf (" %s", file);
    putchar ('\n');
}

bool do_wc (int fd, char const *file_x, off_t current_pos)
{
    bool ok = true;
    char buf[BUFFER_SIZE + 1];
    size_t bytes_read;
    long long lines, words, chars, bytes, linelength;
    lines = words = chars = bytes = linelength = 0;

    bool in_word = false;
    long long linepos = 0;

    while ((bytes_read = read (fd, buf, BUFFER_SIZE)) > 0)
    {
        const char *p = buf;
        if (bytes_read == READ_ERROR)
        {
            ok = false;
            break;
        }

        bytes += bytes_read;
        do
        {
            switch (*p++)
            {
                case '\n':
                    lines++;

                case '\r':
                case '\f':
                    if (linepos > linelength)
                        linelength = linepos;
                    linepos = 0;
                    goto word_separator;

                case '\t':          
                    linepos += 8 - (linepos % 8);   
                    goto word_separator;

                case ' ':
                    linepos++;

                case '\v':
                word_separator:
                    words += in_word;
                    in_word = false;
                    break;
                default:
                    if (isprint (p[-1]))
                    {
                        linepos++;
                        if (isspace (p[-1]) || isnbspace (p[-1]))
                            goto word_separator;
                        in_word = true;
                    }
                break;
            }
        }
        while (--bytes_read);
    }
    if (linepos > linelength)
        linelength = linepos;
    words += in_word;
    chars = bytes;

    write_counts (lines, words, chars, bytes, linelength, file_x);

    total_lines += lines;
    total_words += words;
    total_chars += chars;
    total_bytes += bytes;

    if (linelength > max_line_length)
        max_line_length = linelength;

    return ok;
}

bool wc_file (char const *file)
{
    int fd = open (file, O_RDONLY);
    if (fd == -1)
        return false;
    else
    {
        bool ok = do_wc (fd, file, 0);
        if (close (fd) != 0)
            return false;
        return ok;
    }
}

int wc (int argc, char **argv)
{
    bool ok;
    int optc;
    size_t nfiles;

    print_lines = print_words = print_chars = print_bytes = false;
    print_linelength = false;
    total_lines = total_bytes = total_chars = total_words = 0;   

    while ((optc = getopt_long (argc, argv, "clLmw", longopts, NULL)) != -1)
    switch (optc)
    {
        case 'c':
            print_bytes = true;
            break;

        case 'm':
            print_chars = true;
            break;

        case 'l':
            print_lines = true;
            break;

        case 'w':
            print_words = true;
            break;

        case 'L':
            print_linelength = true;
            break;
    }

    if (! (print_lines || print_words || print_chars || print_bytes || print_linelength))
        print_lines = print_words = print_bytes = true;

    nfiles = argc - optind;

    ok = true;
    for (int i = optind; i < argc; i++)
    {
        char *file_name = argv[i];
        ok &= wc_file (file_name);
    }

    if (nfiles > 1)
        write_counts (total_lines, total_words, total_chars, total_bytes, 
            max_line_length, ("total"));

    return ok ? EXIT_SUCCESS : EXIT_FAILURE;
}

