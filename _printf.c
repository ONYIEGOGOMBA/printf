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
 * print_char - Prints a single character.
 * @args: A va_list containing the character to print.
 *
 * Return: The number of characters printed (always 1).
 */
int print_char(va_list args)
{
    char c = va_arg(args, int);
    return _putchar(c);
}

/**
 * print_string - Prints a string of characters.
 * @args: A va_list containing the string to print.
 *
 * Return: The number of characters printed.
 */
int print_string(va_list args)
{
    char *str = va_arg(args, char *);
    int printed_chars = 0;

    if (str == NULL)
        str = "(null)";

    while (*str)
    {
        _putchar(*str);
        printed_chars++;
        str++;
    }

    return printed_chars;
}

/**
 * print_percent - Prints a percent character.
 * @args: A va_list (unused).
 *
 * Return: Always 1 (number of characters printed).
 */
int print_percent(__attribute__((unused)) va_list args)
{
    _putchar('%');
    return 1;
}

/**
 * print_decimal - Prints a decimal (signed) integer.
 * @args: A va_list containing the integer to print.
 * @printed_chars: A pointer to the counter for printed characters.
 */
int print_decimal(va_list args, int *printed_chars)
{
    int num = va_arg(args, int);
    int divisor = 1;
    int temp = num;

    /* Handle negative numbers */
    if (num < 0)
    {
        _putchar('-');
        (*printed_chars)++;
        num = -num;
    }

    /* Calculate the divisor to print individual digits */
    while (temp > 9)
    {
        temp /= 10;
        divisor *= 10;
    }

    /* Print individual digits */
    while (divisor >= 1)
    {
        int digit = num / divisor;
        char ch = digit + '0';
        _putchar(ch);
        (*printed_chars)++;
        num %= divisor;
        divisor /= 10;
    }
    return *printed_chars;
}

/**
 * print_unsigned - Prints an unsigned integer.
 * @args: A va_list containing the unsigned integer to print.
 *
 * Return: The number of characters printed.
 */
int print_unsigned(va_list args)
{
    unsigned int ui = va_arg(args, unsigned int);
    unsigned int u_divisor = 1;
    int printed_chars = 0;

    /* Calculate the divisor to print individual digits */
    unsigned int u_temp = ui;
    while (u_temp > 9)
    {
        u_temp /= 10;
        u_divisor *= 10;
    }

    /* Print individual digits */
    while (u_divisor >= 1)
    {
        int u_digit = ui / u_divisor;
        char u_ch = u_digit + '0';
        _putchar(u_ch);
        printed_chars++;
        ui %= u_divisor;
        u_divisor /= 10;
    }

    return printed_chars;
}

/**
 * print_octal - Prints an unsigned integer in octal format.
 * @args: A va_list containing the unsigned integer to print.
 *
 * Return: The number of characters printed.
 */
int print_octal(va_list args)
{
    unsigned int ui = va_arg(args, unsigned int);
    char octal[12];
    int o_idx = 0;
    int printed_chars = 0;

    if (ui == 0)
    {
        _putchar('0');
        printed_chars++;
    }
    else
    {
        while (ui != 0)
        {
            octal[o_idx++] = (ui % 8) + '0';
            ui /= 8;
        }

        while (o_idx > 0)
        {
            o_idx--;
            _putchar(octal[o_idx]);
            printed_chars++;
        }
    }

    return printed_chars;
}

/**
 * print_hexadecimal - Prints an unsigned integer in hexadecimal format.
 * @args: A va_list containing the unsigned integer to print.
 * @hex_case: A character specifying the case of hexadecimal letters ('a' or 'A').
 *
 * Return: The number of characters printed.
 */
int print_hexadecimal(va_list args, char hex_case)
{
    unsigned int ui = va_arg(args, unsigned int);
    char hex[12];
    int h_idx = 0;
    int printed_chars = 0;

    if (ui == 0)
    {
        _putchar('0');
        printed_chars++;
    }
    else
    {
        while (ui != 0)
        {
            int remainder = ui % 16;
            hex[h_idx++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + hex_case);
            ui /= 16;
        }

        while (h_idx > 0)
        {
            h_idx--;
            _putchar(hex[h_idx]);
            printed_chars++;
        }
    }

    return printed_chars;
}

/**
 * print_pointer - Prints a pointer address in hexadecimal format.
 * @args: A va_list containing the pointer address to print.
 * @printed_chars: A pointer to the counter for printed characters.
 */
int print_pointer(va_list args, int *printed_chars)
{
    void *ptr = va_arg(args, void *);
    unsigned long int addr = (unsigned long int)ptr;
    char hex[16];
    int h_idx = 0;

    _putchar('0');
    _putchar('x');
    (*printed_chars) += 2;
    if (addr == 0)
    {
        _putchar('0');
        (*printed_chars)++;
    }
    else
    {
        while (addr != 0)
        {
            int remainder = addr % 16;
            hex[h_idx++] = (remainder < 10) ? (remainder + '0') : (remainder - 10 + 'a');
            addr /= 16;
        }

        while (h_idx > 0)
        {
            h_idx--;
            _putchar(hex[h_idx]);
            (*printed_chars)++;
        }
    }
    return *printed_chars;
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
                printed_chars += print_char(args);
                break;
            case 's':
                printed_chars += print_string(args);
                break;
            case '%':
                printed_chars += print_percent(args);
                break;
            case 'd':
            case 'i':
                print_decimal(args, &printed_chars);
                break;
            case 'u':
                printed_chars += print_unsigned(args);
                break;
            case 'o':
                printed_chars += print_octal(args);
                break;
            case 'x':
                printed_chars += print_hexadecimal(args, 'a');
                break;
            case 'X':
                printed_chars += print_hexadecimal(args, 'A');
                break;
            case 'p':
                print_pointer(args, &printed_chars);
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
