#include "main.h"

/**
 * _printf - a function that works similar to the standard printf
 * @format: first argument
 * Return: the number of characters printed to out_put
 */
int _printf(const char *format, ...)
{
	va_list args;
	int char_count = 0;

	va_start(args, format);
	while (format && *format) {
	if	(*format != '%') {
		char_count += write(1, format, 1);
	} else {
		format++;
		switch (*format) {
		case 'c': {
			char c = va_arg(args, int);
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
			char num_str[20];
			int len = sprintf(num_str, "%d", num);
			char_count += write(1, num_str, len);
			break;
		}
		case '%': {
			char_count += write(1, "%", 1);
			break;
		}
		default: {
			char_count += write(1, "%", 1);
			char_count += write(1, format, 1);
		}
		}
	}
	format++;
	}

	va_end(args);
	return (char_count);
}
