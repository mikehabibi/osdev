/* vga_text.c
 *
 * VGA text mode functions for writing to the screen. Note that there is no
 * virtual terminal emulation at this stage, or any type of buffering. This goes
 * directly to the VGA device to be thrown onto the screen.
 */

#include <vga/vga.h>
#include <vga/vga_text.h>

/* Local globals */
static int current_row           = 0;
static int current_column        = 0;
static uint8_t default_color     = 0;
static uint16_t *vga_buf;

/* Initialize the VGA text mode memory space */
void vga_text_init(void)
{
  int i, j;

  current_row   = current_column = 0;
  default_color = make_vga_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
  vga_buf       = VGA_BASE_MEMORY;

  for (i = 0; i < VGA_HEIGHT; i++)
  {
    for (j = 0; j < VGA_WIDTH; j++)
    {
      vga_buf[i * VGA_WIDTH + j] = make_vga_entry(' ', default_color);
    }
  }
}

/* Add a character to the current cursor location */
void vga_text_putc(char c)
{
  if (c == '\n')
  {
    current_column = VGA_WIDTH; /* trick a new line wrap */
  }
  else
  {
    vga_buf[current_row * VGA_WIDTH + current_column++] = make_vga_entry(c, default_color);
  }

  if (current_column >= VGA_WIDTH) 
  {
    current_column = 0;
    current_row++;
  }
  if (current_row >= VGA_HEIGHT)
  {
    current_row = 0; /* wraps to top of screen */
  }
}

/* Write a series of characters to the current cursor location */
void vga_text_write(const char *chars, size_t length)
{
  size_t i;

  for (i = 0; i < length; i++)
  {
    vga_text_putc(chars[i]);
  }
}

/* Write a null-terminated string to the current cursor location */
void vga_text_writestring(const char *string)
{
  int i = 0;

  while (string[i] != 0)
  {
    vga_text_putc(string[i++]);
  }
}
