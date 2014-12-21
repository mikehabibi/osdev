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
    else if ( *format == 'd' )
    {
      format++;
      char str[11]; /* max int size is 10 digits */
      char *strptr = str;
      int val = va_arg(parameters, int);
      int temp;
      /* brute force for now
       * TODO: make this more intelligent */
      temp = val / 1000000000;
      str[0] = '0' + temp;
      val -= (temp * 1000000000);

      temp = val / 100000000;
      str[1] = '0' + temp;
      val -= (temp * 100000000);

      temp = val / 10000000;
      str[2] = '0' + temp;
      val -= (temp * 10000000);

      temp = val / 1000000;
      str[3] = '0' + temp;
      val -= (temp * 1000000);

      temp = val / 100000;
      str[4] = '0' + temp;
      val -= (temp * 100000);

      temp = val / 10000;
      str[5] = '0' + temp;
      val -= (temp * 10000);

      temp = val / 1000;
      str[6] = '0' + temp;
      val -= (temp * 1000);

      temp = val / 100;
      str[7] = '0' + temp;
      val -= (temp * 100);

      temp = val / 10;
      str[8] = '0' + temp;
      val -= (temp * 10);

      temp = val / 1;
      str[9] = '0' + temp;
      val -= (temp * 1);

      str[10] = 0;

      /* remove leading zeroes */
      while (*strptr == '0')
        strptr++;

      print(strptr, strlen(strptr));
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
