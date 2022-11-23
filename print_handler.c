#include "printf.h"

/**
 * print_handler - outputs given arguments based upon types
 * @lyt: layout of strings to print arguments
 * @list: List of arguments to print
 * @ind: ind pointer argumrnt
 * @width: gets width
 * @precision: gets Precision
 * @size: gets Size specification
 *
 * Return: 1 or 2;
 */

int print_handler(const char *lyt, int *ind, va_list list, char buffer[],
		int flags, int width, int precision, int size)
{
	int s; u_len = 0, printed_chars = -1;
	lyt_t lyt_types[] = {
		{'c', print_char}, {'s', print_string}, {'%', print_percent},
		{'i', print_int}, {'d', print_int}, {'b', print_binary},
		{'u', print_unsigned}, {'o', print_octal}, {'x', print_hexadecimal},
		{'X', print_hexa_upper}, {'p', print_pointer}, {'S', print_non_printable},
		{'r', print_reverse}, {'R', print_rot13string}, {'\0', NULL}
	};

	for (s = 0; lyt_types[s].lyt != '\0'; s++)
	{
		if(lyt[*ind] == lyt_types[s].lyt)
		{
			return (lyt_types[s].fcn(list, buffer, flags, width, precision, size));
		}
	}
	if (lyt_types[s].lyt == '\0')
	{
		if (lyt[*ind] == '\0')
			return (-1);
		u_len += write(1, "%%", 1);

		if (lyt[*ind - 1] == ' ')
			u_len += write(1, " ", 1);
		else if (width)
		{
			--(*ind);
			while (lyt[*ind] != ' ' && lyt[*ind] != '%')
				--(*ind);
			if (lyt[*ind] == ' ')
				--(*ind);
			return (1);
		}
		u_len += write(1, &lyt[*ind], 1);

		return (u_len);
	}
	return (printed_chars);
}

