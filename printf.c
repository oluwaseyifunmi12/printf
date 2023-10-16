#include "main.h"
#include <stdarg.h>
#include <unistd.h>

/**
 * _printf - Custom printf function
 * @format: Format string
 * Return: Number of characters printed (excluding null byte)
 */
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

