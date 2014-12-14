/* vga_text.h
 *
 * VGA text mode functions for writing to the screen. Note that there is no
 * virtual terminal emulation at this stage, or any type of buffering. This goes
 * directly to the VGA device to be thrown onto the screen.
 */

#pragma once

#include <stddef.h>

/* Initialize the VGA text mode memory space */
void vga_text_init(void);

/* Add a character to the current cursor location */
void vga_text_putc(char c);

/* Write a series of characters to the current cursor location */
void vga_text_write(const char *chars, size_t length);

/* Write a null-terminated string to the current cursor location */
void vga_text_writestring(const char *string);
