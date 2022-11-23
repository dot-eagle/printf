#include "printf.h"

int is_printable(char);

/** ---- POINTER PRINTF ---- **/

/**
 * print_pointer - Prints the value of a pointer variable
 * @buffer: Buffer array to handle print
 * @width: get width
 * @types: List a of arguments
 * @size: Size
 * @flags: active flags
 * @precision: Precision
 *
 * Return: output
 */

int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
	{
		return (write(1, "(nil)", 5));
	}
	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/* return (write(1, &buffer[s], BUFF_SIZE - s - 1)); */
	return (write_pointer(buffer, ind, length, width,
				flags, padd, extra_c, padd_start));
}

/** ---- ASCII: THE NON-PRINTABLES ---- **/

/**
 * print_non_printable - Prints ascii codes of non printable chars in hex
 * @flags:  Calculates active flags
 * @types: Lista of arguments
 * @size: Size
 * @buffer: Buffer array to handle print
 * @width: get width
 * @precision: Precision
 *
 * Return:outputs
 */

int print_non_printable(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int s = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[s] != '\0')
	{
		if (is_printable(str[s]))
			buffer[s + offset] = str[s];
		else
			offset += append_hexa_code(str[s], buffer, s + offset);
		s++;
	}
	buffer[s + offset] = '\0';

	return (write(1, buffer, s + offset));
}

/** ---- STRINGS IN ROT13 ---- **/

/**
 * print_rot13string - Print a string in rot13
 * @size: Size
 * @width: get width
 * @buffer: Buffer array to handle print
 * @precision: Precision
 * @types: Lista of arguments
 * @flags: active flags
 *
 * Return: strings
 */

int print_rot13string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char *str, v;
	unsigned int s, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";

	for (s = 0; str[s]; s++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[s])
			{
				v = out[j];
				write(1, &v, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			v = str[s];
			write(1, &v, 1);
			count++;
		}
	}
	return (count);
}
