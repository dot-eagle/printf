#include "printf.h"

/**
 * do_print - Evaluates if parameter is printable
 * @c: parameter to evaluate
 *
 * Return: 1 if printable else 0
 */

int do_print(char c)
{
	if (c >= 32 && c < 127)
	{
		return (1);
	}
	else
		return (0);
}

/**
 * append_hexa_code - Append ascci code in hexa to buffer array
 * @buffer: buffer array
 * @ascii_code: ASSCI CODE
 * @s: Index at which to start appending.
 *
 * Return: Alway
 */

int append_hexa_code(char ascii_code, char buffer[], int s)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[s++] = '\\';
	buffer[s++] = 'x';

	buffer[s++] = map_to[ascii_code / 16];
	buffer[s] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - Verifies if parameter is digit
 * @c: parameter to be evaluated
 *
 * Return: 1 if c is a digit, else 0
 */

int is_digit(char c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	else
		return (0);
}

/**
 * convert_size_number - Casts a number to the specified data size
 * @num: Number to be casted
 * @size: parameter of type to cast
 *
 * Return: num
 */

long int convert_size_number(long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
	{
		return ((short)num);
	}

	return ((int)num);
}

/**
 * convert_size_unsgnd - Casts a number to the specified size
 * @num: Number to be casted
 * @size: parameter of type to cast
 *
 * Return: num
 */

long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
	{
		return (num);
	}
	else if (size == S_SHORT)
	{
		return ((unsigned short)num);
	}

	return ((unsigned int)num);
}

