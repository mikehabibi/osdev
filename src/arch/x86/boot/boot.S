/* boot.S
 *
 * Bootstrap our kernel from a multiboot loader, such as GRUB. This file is
 * a modified version of the example files from the Multiboot Specification
 * and the Bare Bones tutorial from osdev.org.
 *
 * See LICENSE for license information
 */

#define ASM_FILE 1
#include <multiboot.h>

#define MULTIBOOT_HEADER_FLAGS    0x00000003 /* mem map and align */

#define STACK_SIZE                0x00004000 /* 16KB */

.align 4
.section .multiboot
        .long   MULTIBOOT_HEADER_MAGIC
        .long   MULTIBOOT_HEADER_FLAGS
        .long   -(MULTIBOOT_HEADER_MAGIC + MULTIBOOT_HEADER_FLAGS)

.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip STACK_SIZE
stack_top:

.section .text
.global _start
.type _start, @function

_start:
        # We need to setup the stack because literally nothing is setup (ok not
        # literally)
        movl    $stack_top, %esp

        # Now that the stack is setup, we can transition to C
        call    kernel_main

        # If we ever exit this, then we need to just halt the processor
        cli
        hlt
.haltloop:
        jmp   .haltloop

.size .start, (. - _start)

#undef ASM_FILE

