/* init.c
 *
 * C entry-point for our kernel. Initialize the kernel and get the ball rolling.
 * The only thing that has happened before calling kernel_main is that we have
 * setup a 16KB stack from our bootstrap.
 */

#include <kernel/kernel.h>
#include <vga/vga_text.h>

void kernel_main(void);

void kernel_main(void)
{
  vga_text_init();

  printf("Welcome to the kernel!\n");
  printk("This is a test of printk %s...\n", "functionality");
  return;
}
