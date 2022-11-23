#include "printf.h"

/** ---- UNSIGNED DIGITS ---- **/

/**
 * print_unsigned - Prints UNSUGNED DIGITS
 * @flags: active flags
 * @size: Size
 * @types: List a of arguments
 * @width: get width
 * @buffer: Buffer array to handle print
 * @precision: Precision
 *
 * Return: unsigned chars to print
 */

int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[s--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[s--] = (num % 10) + '0';
		num /= 10;
	}
	s++;

	return (write_unsgnd(0, s, buffer, flags, width, precision, size));
}


/** ---- UNSIGNED DIGITS IN OCTAL NOTATION ---- **/

/**
 * print_octal - Prints an unsigned digits in octal base
 * @types: Lista of arguments
 * @flags: active flags
 * @width: get width
 * @buffer: Buffer array to handle print
 * @size: Size
 * @precision: Precision
 *
 * Return: octal values
 */

int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
	{
		buffer[s--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[s--] = (num % 8) + '0';
		num /= 8;
		s++;
	}

	if (flags && F_HASH && init_num != 0)
	{
		buffer[s--] = '0';
	}
	return (write_unsgnd(0, s, buffer, flags, width, precision, size));
}

/** ---- UNSIGNED DIGITS IN HEXADECIMAL NOTATION --- **/

/**
 * print_hexadecimal - Prints an unsigned hexadecimal numbers
 * @size: Size
 * @types: Lista of arguments
 * @precision: Precision
 * @flags: active flags
 * @buffer: Buffer array to handle print
 * @width: get width
 *
 * Return: unsigned hexadecimals
 */

int print_hexadecimal(va_list types, char buffer[],
		int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
				flags, 'x', width, precision, size));
}

/** ---- UNSIGNED UPPER HEXADECIMAL DIGITS ---- **/

/**
 * print_hexa_upper - Prints an unsigned upper hexadecimals
 * @types: Lista of arguments
 * @width: get width
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @size: Size
 * @precision: Precision
 *
 * Return: upper hex chars
 */

int print_hexa_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
				flags, 'X', width, precision, size));
}

/** --- PRINTS LOWER OR UPPER DIGITS IN HEXA NOTATION --- **/

/**
 * print_hexa - Prints lower or upper hexadecimals
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @map_to: Array of values to map numbers
 * @flags: active flags
 * @flag_ch: active flag chars
 * @size: Size
 * @precision: Precision
 * @width: get width
 *
 * Return: Hexx
 */


int print_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	if (num == 0)
	{
		buffer[s--] = '0';
	}
	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[s--] = map_to[num % 16];
		num /= 16;

		if (flags & F_HASH && init_num != 0)
		{
			buffer[s--] = flag_ch;
			buffer[s--] = '0';
		}
		s++;
	}
	return (write_unsgnd(0, s, buffer, flags, width, precision, size));
}
