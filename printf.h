#ifndef _PRINTF_H
#define _PRINTF_H

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stddef.h>
#include <stdarg.h>

#define UNUSED(x) (void)(x)
#define BUFF_SIZE 1024
/* -- FLAGS -- */
#define F_MINUS 1
#define F_PLUS 2
#define F_ZERO 4
#define F_HASH 8
#define F_SPACE 16
/* -- SIZES -- */
#define S_LONG 2
#define S_SHORT 1

/**
 * struct lyt - Struct op
 * @lyt: formats
 * @fcn: The associated function
 */

struct lyt
{
	char lyt;
	int (*fcn)(va_list, char[], int, int, int, int);
};

/**
 * typedef struct lyt lyt_t - Struct ops
 * @lyt: Formats
 * @lyt_t: Associated function
 */

typedef struct lyt lyt_t;
int _printf(const char *format, ...);
int print_handler(const char *lyt, int *, va_list list,
		char buffer[], int flags, int width, int precision, int size);


/** --------------LIST OF PRINT FUNCTIONS ------------ **/


/* A list of functions for printing C strings and chars */
int print_char(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_string(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_percent(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* --- Listing functions that print digits --- */
int print_hexa_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_binary(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_hexa(va_list types, char map_to[], char buffer[], int flags,
		char flag_ch, int width, int precision, int size);
int print_unsigned(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_octal(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_hexadecimal(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_int(va_list types, char buffer[], int flags,
		int width, int precision, int size);
int print_hexa_upper(va_list types, char buffer[], int flags,
		int width, int precision, int size);


/* A function that prints the non printable characters */
int print_non_printable(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* --- A Funcion to print addresses in memory --- */
int print_pointer(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* --- List of funciotns to format and  handle specifiers --- */
int get_precision(const char *format, int *, va_list list);
int get_flags(const char *format, int *);
int get_size(const char *format, int *);
int get_width(const char *format, int *, va_list list);


/* --- Function tthat prints strings in reverse --- */
int print_reverse(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* --- A function to print a string in rot 13 --- */
int print_rot13string(va_list types, char buffer[], int flags,
		int width, int precision, int size);

/* --- List of Width handlers --- */
int handle_write_char(char c, char buffer[], int flags,
		int width, int precision, int size);
int write_pointer(char buffer[], int ind, int length, int width,
		int flags, char padd, char extra_c, int padd_start);
int write_number(int is_positive, int ind, char buffer[], int flags,
		int width, int precision, int size);
int write_unsgnd(int is_negative, int ind, char buffer[],
		int flags, int width, int precision, int size);
int write_num(int ind, char buffer[], int flags, int precision,
		int width, int length, char padd, char extra_c);


/** -------- UTILS ------------ **/
int is_digit(char);
int do_print(char);
int append_hexa_code(char, char[], int);
long int convert_size_unsgnd(unsigned long int num, int size);
long int convert_size_number(long int num, int size);


#endif /* PRINTF_H */
