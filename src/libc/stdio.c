/* stdio.c
 *
 * I/O routines
 */

#include <stdio.h>
#include <error.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#ifdef __KERNEL
#include <vga/vga_text.h>
#endif

int putchar(char c)
{
  int ret = E_OK;

#ifdef __KERNEL
  vga_text_putc(c);
#else
  /* not supported yet */
  ret = E_NOSUPPORT;
#endif

  return ret;
}

int puts(const char *string)
{
  return printf("%s\n", string);
}

static void print(const char *data, size_t length)
{
  size_t i = 0;

  for (i = 0; i < length; i++)
  {
    putchar(data[i]);
  }
}

/* I didn't want to write printf myself, so I copy/pasted implementation from
 * osdev.org wiki
 */
int printf(const char * __restrict__ format, ...)
{
  va_list parameters;
  va_start(parameters, format);

  int written = 0;
  size_t amount;
  bool rejected_bad_specifier = false;

  while ( *format != '\0' )
  {
    if ( *format != '%' )
    {
print_c:
      amount = 1;
      while ( format[amount] && format[amount] != '%' )
        amount++;
      print(format, amount);
      format += amount;
      written += amount;
      continue;
    }

    const char* format_begun_at = format;

    if ( *(++format) == '%' )
      goto print_c;

    if ( rejected_bad_specifier )
    {
incomprehensible_conversion:
      rejected_bad_specifier = true;
      format = format_begun_at;
      goto print_c;
    }

    if ( *format == 'c' )
    {
      format++;
      char c = (char) va_arg(parameters, int /* char promotes to int */);
      print(&c, sizeof(c));
    }
    else if ( *format == 's' )
    {
      format++;
      const char* s = va_arg(parameters, const char*);
      print(s, strlen(s));
    }
    else
    {
      goto incomprehensible_conversion;
    }
  }

  va_end(parameters);

  return written;
}
