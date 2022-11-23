#include "printf.h"

void print_buffer(char buffer[], int *buff_ind);

/**
 * _printf - produces output according to a format
 * @format: character string
 *
 * Return: formatted output
 */

int _printf(const char *format, ...)
{
	int s, printed = 0, printed_chars = 0;
	int flags, width, precision, size, buff_ind = 0;
	va_list list;
	char buffer[BUFF_SIZE];

	if (format == NULL)
		return (-1);

	va_start(list, format);
	s = 0;
	while (format && format[s] != '\0')
	{
		if (format[s] != '%')
		{
			buffer[buff_ind++] = format[s];
			if (buff_ind == BUFF_SIZE)
			{
				print_buffer(buffer, &buff_ind);
			}
			/* write(1, &format[i], 1);*/
			printed_chars++;
		}
		else
		{
			print_buffer(buffer, &buff_ind);
			flags = get_flags(format, &s);
			width = get_width(format, &s, list);
			precision = get_precision(format, &s, list);
			size = get_size(format, &s);
			++s;

			printed = handle_print(format, &s, list, buffer, flags,
					width, precision, size);

			if (printed == -1)
				return (-1);
		}
		s++;
	}
	print_buffer(buffer, &buff_ind);
	va_end(list);
	return (printed_chars);
}

/**
 * print_buffer - Prints the contents of existing buffer if any
 * @buffer: Array of chars
 * @buff_ind: Index at which to add chars
 *
 * return: nothing
 */

void print_buffer(char buffer[], int *buff_ind)
{
	if (*buff_ind > 0)
		write(1, &buffer[0], *buff_ind);

	*buff_ind = 0;
}
