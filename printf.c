#include "main.h"

/**
 * write_char - a function that prints to standard output
 * @fd: file number
 * @c: character to be printed
 * Return: output
 */

int write_char(int fd, char c)
{
	return (write(fd, &c, 1));
}

/**
 * _printf - a function that works similar to the standard printf
 * @format: first argument
 * Return: the number of characters printed to out_put
 */

int _printf(const char *format, ...)
{
	va_list list;
	int ch_count = 0;

	va_start(list, format);
	while (format && *format)
	{
		if (*format != '%')
		{
			ch_count += write_char(1, *format);
		} else
		{
			format++;
	switch (*format)
	{
		case 'c': {
			char c = va_arg(list, int);

			ch_count += write_char(1, c);
			break;
		}
		case 's': {
			char *s = va_arg(list, char *);

			while (*s) {
			ch_count += write_char(1, *s);
			s++;
		}
			break;
		}
		case 'd':
		case 'i': {
			int num = va_arg(list, int);

			char num_str[20];
			int len = sprintf(num_str, "%d", num);
			ch_count += write(1, num_str, len);
		break;
		}
		case '%': {
			ch_count += write_char(1, '%');
			break;
		}
		default: {
			ch_count += write_char(1, '%');
			ch_count += write_char(1, *format);
		}
		}
	}
	format++;
	}
	va_end(list);
	return (ch_count);
}
