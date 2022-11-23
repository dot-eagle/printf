#include "printf.h"

/**
 * get_width - width calculator
 * @format: character argument
 * @list: list of arguments
 * @s: argument
 *
 * Return: width
 */

int get_width(const char *format, int *s, va_list list)
{
	int curr_s;
	int width = 0;

	for (curr_s = *s + 1; format[curr_s] != '\0'; curr_s++)
	{
		if (is_digit(format[curr_s]))
		{
			width *= 10;
			width += format[curr_s] - '0';
		}
		else if (format[curr_s] == '*')
		{
			curr_s++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*s = curr_s - 1;

	return (width);
}
