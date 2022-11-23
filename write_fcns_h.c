#include "printf.h"

/** ---- WRITE FUNCTIONS & HANDLERS ---- **/

/**
 * handle_write_char - Prints a string
 * @buffer: Buffer array to handle print
 * @width: get width
 * @c: char types
 * @flags: active flags
 * @size: Size spice
 * @precision: precision
 *
 * Return: printed chars
 */

int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size)
{
	/* char is stored at left and paddind at buffer's right */

	int s = 0;
	char padd = ' ';

	UNUSED(precision);
	UNUSED(size);

	if (flags & F_ZERO)
		padd = '0';

	buffer[s++] = c;
	buffer[s++] = '\0';

	if (width > 1)
	{
		buffer[BUFF_SIZE - 1] = '\0';
		for (s = 0; s < width - 1; s++)
			buffer[BUFF_SIZE - s - 2] = padd;

		if (flags & F_MINUS)
			return (write(1, &buffer[0], 1) +
					write(1, &buffer[BUFF_SIZE - s - 1], width - 1));
	}

	return (write(1, &buffer[0], 1));
}

/** ---- WRITE DIGIITS HANDLER ---- **/

/**
 * write_number - take digits
 * @ind: parameter
 * @is_negative: List of arguments
 * @buffer: Buffer array to handle print
 * @size: Size
 * @flags: active flags
 * @precision: precision
 * @width: get width
 *
 * Return: output
 */

int write_number(int is_negative, int ind, char buffer[], int flags,
		int width, int precision, int size)
{
	int length = BUFF_SIZE - ind - 1;
	char padd = ' ', extra_ch = 0;

	UNUSED(size);

	if ((flags & F_ZERO) && !(flags & F_MINUS))
	{
		padd = '0';
	}
	if (is_negative)
		extra_ch = '-';
	else if (flags & F_PLUS)
		extra_ch = '+';
	else if (flags & F_SPACE)
		extra_ch = ' ';

	return (write_num(ind, buffer, flags, width,
				precision, length, padd, extra_ch));
}

/**
 * write_num - Write a number using a bufffer array
 * @buffer: Buffer array
 * @width: width
 * @length: Number length
 * @ind: Index at which the number starts on the buffer
 * @extra_c: Extra char
 * @flags: Flags
 * @padd: Pading char
 * @prec: Precision specifier
 *
 * Return: o
 */

int write_num(int ind, char buffer[], int flags, int width,
		int prec, int length, char padd, char extra_c)
{
	int s, padd_start = 1;

	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0' && width == 0)
		return (0);/* printf(".0d", 0)  no char is printed */
	if (prec == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		buffer[ind] = padd = ' ';/* width is displayed with padding ' ' */
	if (prec > 0 && prec < length)
		padd = ' ';
	while (prec > length)
		buffer[--ind] = '0', length++;
	if (extra_c != 0)
		length++;
	if (width > length)
	{
		for (s = 1; s < width - length + 1; s++)
			buffer[s] = padd;
		buffer[s] = '\0';
		if (flags & F_MINUS && padd == ' ')/* Asign extra char to left of buffer */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[1], s - 1));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buff */
		{
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[1], s - 1) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			return (write(1, &buffer[padd_start], s - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start)));
		}
	}
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], length));
}

/**
 * write_unsgnd - Writes unsigned digits
 * @ind: Index at which the number starts in the buffer
 * @flags: Flags
 * @is_negative:indicating if the num is signed
 * @size: Size
 * @buffer: Array of chars
 * @width: Width
 * @precision: Precision
 *
 * Return: written chars
 */

int write_unsgnd(int is_negative, int ind,  char buffer[], int flags,
		int width, int precision, int size)
{
	/* The number is stored at the bufer's right and starts at position s */
	int length = BUFF_SIZE - ind - 1, s = 0;
	char padd = ' ';

	UNUSED(is_negative);
	UNUSED(size);

	if (precision == 0 && ind == BUFF_SIZE - 2 && buffer[ind] == '0')
		return (0);
	/* printf(".0d", 0)  no char is printed */
	if (precision > 0 && precision < length)
		padd = ' ';
	while (precision > length)
	{
		buffer[--ind] = '0';
		length++;
	}
	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (width > length)
	{
		for (s = 0; s < width - length; s++)
			buffer[s] = padd;
		buffer[s] = '\0';
		if (flags & F_MINUS)	/* Asign extra char to left of buffer [buffer>padd]*/
		{
			return (write(1, &buffer[ind], length) + write(1, &buffer[0], s));
		}
		else /* Asign extra char to left of padding [padd>buffer]*/
		{
			return (write(1, &buffer[0], s) + write(1, &buffer[ind], length));
		}
	}
	return (write(1, &buffer[ind], length));
}

/**
 * write_pointer - Write the address of memory
 * @padd: Char representing the paddin
 * @padd_start: Index at which padding should start
 * @flags: Flags
 * @extra_c: Char representing extra char
 * @ind: Index
 * @width: width
 * @buffer: Arrays of chars
 * @length: Length of number
 *
 * Return: written values
 */

int write_pointer(char buffer[], int ind, int length, int width,
		int flags, char padd, char extra_c, int padd_start)
{
	int s;

	if (width > length)
	{
		for (s = 3; s < width - length + 3; s++)
			buffer[s] = padd;
		buffer[s] = '\0';
		if (flags & F_MINUS && padd == ' ') /* Asign extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[ind], length) + write(1, &buffer[3], s - 3));
		}
		else if (!(flags & F_MINUS) && padd == ' ')/* extra char to left of buffer */
		{
			buffer[--ind] = 'x';
			buffer[--ind] = '0';
			if (extra_c)
				buffer[--ind] = extra_c;
			return (write(1, &buffer[3], s - 3) + write(1, &buffer[ind], length));
		}
		else if (!(flags & F_MINUS) && padd == '0')/* extra char to left of padd */
		{
			if (extra_c)
				buffer[--padd_start] = extra_c;
			buffer[1] = '0';
			buffer[2] = 'x';
			return (write(1, &buffer[padd_start], s - padd_start) +
					write(1, &buffer[ind], length - (1 - padd_start) - 2));
		}
	}
	buffer[--ind] = 'x';
	buffer[--ind] = '0';
	if (extra_c)
		buffer[--ind] = extra_c;
	return (write(1, &buffer[ind], BUFF_SIZE - ind - 1));
}
