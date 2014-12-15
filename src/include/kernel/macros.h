/* macros.h
 *
 * Common macros for the kernel
 */

#include <stdio.h>

#define printk(...) { \
  printf("%s:%d: ", __FILE__, __LINE__); \
  printf(__VA_ARGS__); \
}
