#include "printf.h"

/**
 * get_precision - Calculates the precision
 * @format: a character string argument
 * @list: list of arguments
 * @s: arguments
 *
 * Return: pecision
 */

int get_precision(const char *format, int *s, va_list list)
{
	int curr_s = *s + 1;
	int precision = -1;

	if (format[curr_s] != '.')
	{
		return (precision);
	}
	precision = 0;

	for (curr_s += 1; format[curr_s] != '\0'; curr_s++)
	{
		if (is_digit(format[curr_s]))
		{
			precision *= 10;
			precision += format[curr_s] - '0';
		}
		else if (format[curr_s] == '*')
		{
			curr_s++;
			precision = va_arg(list, int);
			break;
		}
		else
			break;
	}
	*s = curr_s - 1;

	return (precision);
}
