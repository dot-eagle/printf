#include "printf.h"


/** --- CHARS --- **/

/**
 * print_char - Print chars
 * @types: arguments
 * @buffer: Buffer array to handle print
 * @flags: flags
 * @size: Size specifier
 * @width: Width
 * @precision: precision
 *
 * Return: chars
 */

int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, flags, width, precision, size));
}

/** ---- STRINGS ---- **/

/**
 * print_string - Prints a string
 * @types: arguments
 * @buffer: Buffer array to handle print
 * @size: Size
 * @width: get width
 * @flags: active flags
 * @precision: Precision
 *
 * Return: chars
 */

int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = 0, s;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		{
			str = "      ";
		}
	}
	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
	{
		length = precision;
	}
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (s = width - length; s > 0; s--)
				write(1, " ", 1);
			return (width);
		}
		else
			for (s = width - length; s > 0; s--)
			{
				write(1, " ", 1);
				write(1, &str[0], length);
				return (width);
			}
	}
	return (write(1, str, length));
}

/** ---- PERCENTAGE SIGN ---- **/

/**
 * print_percent - Prints a percent sign
 * @buffer: Buffer array to handle print
 * @width: get width
 * @size: Size
 * @types: Lista of arguments
 * @precision: Precision
 * @flags:  Calculates active flags
 */

int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	return (write(1, "%%", 1));
}


/** ---- INTEGERS ----- **/

/**
 * print_int - Print integers
 * @buffer: Buffer array to handle print
 * @size: Size specifier
 * @types: Lista of arguments
 * @precision: Precision
 * @flags:  Calculates active flags
 * @width: get width
 *
 * Return: printed integers
 */

int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	int s = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
	{
		buffer[s--] = '0';
	}

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}
	while (num > 0)
	{
		buffer[s--] = (num % 10) + '0';
		num /= 10;
	}
	s++;

	return (write_number(is_negative, s, buffer, flags, width, precision, size));
}

/** ---- PRINT BINARY ---- **/

/**
 * print_binary - Prints an unsigned number
 * @size: Size specifier
 * @width: get width
 * @types: Lista of arguments
 * @size: Size
 * @flags: active flags
 * @buffer: Buffer array to handle print
 */

int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size)
{
	unsigned int n, m, s, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;

	for (s = 1; s < 32; s++)
	{
		sum += a[s];
		if (sum || s == 31)
		{
			char z = '0' + a[s];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
