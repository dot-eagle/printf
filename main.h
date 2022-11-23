#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdarg.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024
/* FLAGS */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
/* SIZES */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct fmtz - Struct op
 * @fmtz: formats
 * @fnc: The associated function
 */

struct fmtz
{
	char fmtz;
	int (*fnc)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct fmtz fmtz_t - Struct ops
 * @fmtz: Formats
 * @fmtz_t: Associated function
 */

typedef struct fmt fmt_t;
int _printf(const char *format, ...);
int handle_print(const char *fmt, int *i, va_list list,
		char buffer[], int flags, int width, int precision, int size);

#endif /* _PRINTF_H */
