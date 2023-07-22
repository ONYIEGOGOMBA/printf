#include <unistd.h>
#include <stdarg.h>
#include "main.h"
/**
 * _putchar - Custom putchar function to write a single character to stdout
 * @c: The character to be written
 * Return: On success, returns the number of characters written (1)
 * On error, returns -1
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
/**
 * _printf - Custom printf function
 * @format: The format string
 * Return: The number of characters printed (excluding the null byte)
 * Returns -1 if an error occurs
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
					{
						char c = va_arg(args, int);
				
						_putchar(c);
						printed_chars++;
						break;
					}
				case 's':
					{
						char *str = va_arg(args, char *);
					
						if (!str)
							str = "(null)";
						while (*str)
						{
							_putchar(*str);
							printed_chars++;
							str++;
						}
						break;
					}
				case '%':
					_putchar('%');
					printed_chars++;
					break;
				default:
					_putchar('%');
					_putchar(*format);
					printed_chars += 2;
			}
		}
		format++;
	}
	va_end(args);
	return (printed_chars);
}
