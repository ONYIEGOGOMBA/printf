#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>

#define BUFFER_SIZE 1024

int _printf(const char *format, ...);
int _putchar(char c);
static void handle_string(va_list args, int *printed_chars);
static void handle_char(va_list args, int *printed_chars);

#endif
