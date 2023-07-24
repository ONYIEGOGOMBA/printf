#include <unistd.h>
#include <stdarg.h>
#include "main.h"

/**
 * _putchar - Helper function to write a single character to stdout.
 * @c: The character to be written.
 * Return: On success, 1. On error, -1 is returned.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * handle_char - Helper function to handle the 'c' specifier in _printf.
 * @args: The va_list containing the arguments passed to _printf.
 * @printed_chars: A pointer to the counter for printed characters.
 */
static void handle_char(va_list args, int *printed_chars)
{
	char c = va_arg(args, int);

	_putchar(c);
	(*printed_chars)++;
}

/**
 * handle_string - Helper function to handle the 's' specifier in _printf.
 * @args: The va_list containing the arguments passed to _printf.
 * @printed_chars: A pointer to the counter for printed characters.
 */
static void handle_string(va_list args, int *printed_chars)
{
	char *str = va_arg(args, char *);

	if (!str)
		str = "(null)";
	while (*str)
	{
		_putchar(*str);
		(*printed_chars)++;
		str++;
	}
}

/**
 * _printf - Custom printf function that produces output according to a format.
 * @format: The format string containing zero or more directives.
 * Return: The number of characters printed.
 */
int _printf(const char *format, ...)
{
	int printed_chars = 0;
	va_list args;

	va_start(args, format);
	while (*format)
	{
		if (*format != '%')
		{
			_putchar(*format);
			printed_chars++;
		}
		else
		{
			format++;
			switch (*format)
			{
				case 'c':
					handle_char(args, &printed_chars);
					break;
				case 's':
					handle_string(args, &printed_chars);
					break;
				case '%':
					_putchar('%');
					printed_chars++;
					break;
				default:
					_putchar('%');
					_putchar(*format);
					printed_chars += 2;
					break;
			}
		}
		format++;
	}
	va_end(args);
	return (printed_chars);
}


