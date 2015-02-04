/* init.c
 *
 * C entry-point for our kernel. Initialize the kernel and get the ball rolling.
 * The only thing that has happened before calling kernel_main is that we have
 * setup a 16KB stack from our bootstrap.
 */

#include <kernel/kernel.h>
#include <vga/vga_text.h>
#include <bios.h>
#include <multiboot.h>

void kernel_main(multiboot_info_t *mbi, unsigned int magic);

void kernel_main(multiboot_info_t *mbi, unsigned int magic)
{
  vga_text_init();

  printf("Welcome to the kernel!\n");
  printk("Grabbing memory map from BIOS...\n");

  if (magic == MULTIBOOT_BOOTLOADER_MAGIC)
  {
    /* booted by GRUB or multiboot-compliant bootloader.
     * mbi is valid
     */
    printk("Multiboot-compliant!\n");
    printk("flags = %d\n", mbi->flags);
    printk("mem_lower = %d\n", mbi->mem_lower);
    printk("mem_upper = %d\n", mbi->mem_upper);
  }
  else
  {
    printk("NOT Multiboot-compliant!");
    /* BOCHS_TRAP;
    ret = bios_detect_memory();
    printk("Ret = %d\n", ret);
    */
  }

  return;
}
