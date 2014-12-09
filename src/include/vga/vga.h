/* vga.h
 *
 * VGA definitions (text-mode only!)
 */

#pragma once

#include <stdint.h>

static uint16_t * const VGA_BASE_MEMORY = (uint16_t *)0xB8000;

static const int VGA_HEIGHT = 25;
static const int VGA_WIDTH  = 80;

/* color codes for text-mode VGA */
static const int VGA_COLOR_BLACK          = 0;
static const int VGA_COLOR_BLUE           = 1;
static const int VGA_COLOR_GREEN          = 2;
static const int VGA_COLOR_CYAN           = 3;
static const int VGA_COLOR_RED            = 4;
static const int VGA_COLOR_MAGENTA        = 5;
static const int VGA_COLOR_BROWN          = 6;
static const int VGA_COLOR_LIGHT_GREY     = 7;
static const int VGA_COLOR_DARK_GREY      = 8;
static const int VGA_COLOR_LIGHT_BLUE     = 10;
static const int VGA_COLOR_LIGHT_GREEN    = 11;
static const int VGA_COLOR_LIGHT_CYAN     = 12;
static const int VGA_COLOR_LIGHT_RED      = 13;
static const int VGA_COLOR_LIGHT_MAGENTA  = 14;
static const int VGA_COLOR_WHITE          = 15;

static inline uint8_t make_vga_color(int fg, int bg)
{
  return (uint8_t)fg | (uint8_t)bg << 4;
}

static inline uint16_t make_vga_entry(char c, uint8_t color)
{
  return (uint16_t)c | (uint16_t)color << 8;
}
