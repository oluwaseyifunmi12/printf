#include "main.h"
#include <stdarg.h>
#include <unistd.h>
#include <stdio.h> /* Include the <stdio.h> header for sprintf */

int _printf(const char *format, ...) {
    va_list args;
    int char_count = 0;

    va_start(args, format);

    while (format && *format) {
        if (*format != '%') {
            char_count += write(1, format, 1); /* Write a character to stdout */
        } else {
            format++; /* Move past '%' */
            switch (*format) {
                case 'c': {
                    char c = va_arg(args, int); /* char is promoted to int in varargs */
                    char_count += write(1, &c, 1);
                    break;
                }
                case 's': {
                    char *s = va_arg(args, char *);
                    while (*s) {
                        char_count += write(1, s, 1);
                        s++;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    int num = va_arg(args, int);
                    char num_str[20]; /* A reasonable buffer size for an int */
                    int len = sprintf(num_str, "%d", num);
                    char_count += write(1, num_str, len);
                    break;
                }
                case '%': {
                    char_count += write(1, "%", 1);
                    break;
                }
                default: {
                    char_count += write(1, "%", 1); /* Handle unknown conversion specifiers */
                    char_count += write(1, format, 1);
                }
            }
        }
        format++;
    }

    va_end(args);
    return char_count;
}

