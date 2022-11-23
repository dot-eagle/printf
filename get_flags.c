#include "printf.h"

/**
 * get_flags - to compute active flags
 * @format: a character string argument
 * @s: parameter
 *
 * Return: Flags
 */

int get_flags(const char *format, int *s)
{
	/* - + 0 # ' ' */
	/* 1 2 4 8  16 */
	int m, curr_s;
	int flags = 0;
	const char FLAGS_CH[] = {'-', '+', '0', '#', ' ', '\0'};
	const int FLAGS_ARR[] = {F_MINUS, F_PLUS, F_ZERO, F_HASH, F_SPACE, 0};

	for (curr_s = *s + 1; format[curr_s] != '\0'; curr_s++)
	{
		for (m = 0; FLAGS_CH[m] != '\0'; m++)
		{
			if (format[curr_s] == FLAGS_CH[m])
			{
				flags |= FLAGS_ARR[m];
				break;
			}
		}
		if (FLAGS_CH[m] == 0)
			break;
	}
	*s = curr_s - 1;

	return (flags);
}
