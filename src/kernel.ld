ENTRY(_start)

SECTIONS
{
  /* Start at 1MB offset */
  . = 1M;

  /* Multiboot header and text section */
  .text BLOCK(4K) : ALIGN(4K)
  {
    *(.multiboot)
    *(.text)
  }

  /* Read-only data */
  .rodata BLOCK(4K) : ALIGN(4K)
  {
    *(.rodata)
  }

  /* Read-write data */
  .data BLOCK(4K) : ALIGN(4K)
  {
    *(.data)
  }

  /* Uninitialized data and stack */
  .bss BLOCK(4K) : ALIGN(4K)
  {
    *(COMMON)
    *(.bss)
    *(.bootstrap_stack)
  }
}
