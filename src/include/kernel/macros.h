/* macros.h
 *
 * Common macros for the kernel
 */

#pragma once

#include <stdio.h>

#define printk(...) { \
  printf("%s:%d: ", __FILE__, __LINE__); \
  printf(__VA_ARGS__); \
}

#define BOCHS_TRAP __asm__("xchgw %bx, %bx")
