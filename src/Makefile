# NOTE: This is my attempt at a non-recursive Makefile. For more information,
# read "Recursive Make Considered Harmful".

# Architecture. Eventually this may be set by config options, but for now since
# we know this is a simple x86 OS, no need to do any of that now.
ARCH     := x86

#######################
# IMAGES
#######################

# Final image name for OS
OS_IMAGE := osdev.bin

# libc library for kernel
KERNEL_LIBC := libc/libk.a

# libc library for user applications
USER_LIBC := libc/libc.a

########################
# Toolchain information
########################
CROSS := i686-elf-
CC    := $(CROSS)gcc
LD    := $(CROSS)ld
AS    := $(CROSS)as
AR    := $(CROSS)ar
CPP   := $(CROSS)cpp

# Handling quiet vs verbose
ifeq ($(V),1)
	Q1 := "true"
	Q2 :=
else
	Q1 := echo
	Q2 := @
endif

# Common compilation flags (for kernel builds)
ROOTDIR  := $(CURDIR)

CFLAGS   += -nostdlib -lgcc -std=gnu99 -MMD -ffreestanding
CFLAGS   += -I$(ROOTDIR)/include
CFLAGS   += -I$(ROOTDIR)/libc/include
CFLAGS   += -Wall -Werror -Wextra -pedantic -Wshadow -Wpointer-arith \
            -Wwrite-strings -Wmissing-prototypes -Wmissing-declarations \
            -Wredundant-decls -Wnested-externs -Winline -Wno-long-long \
            -Wuninitialized -Wstrict-prototypes -Wcast-align
# Used to indicate that we are compiling kernel code, not userspace code
CFLAGS   += -D__KERNEL
#CFLAGS   += -Wconversion
#CFLAGS   += -v

LDFLAGS  += -nostdlib -lgcc

ASFLAGS  += $(CFLAGS)

ARFLAGS  := rcs

#######
# Rules
#######
.PHONY: all iso clean depclean superclean

# Default rule 'all' comes before everything!
all: $(OS_IMAGE)
	@echo "Successfully built kernel."

SRCDIRS := arch/$(ARCH) kernel drivers libc

#SRCS := $(shell find $(SRCDIRS) -type f -name "*.c" -o -name "*.S")
#HDRS := $(shell find $(SRCDIRS) -type f -name "*.h")
SRCS    :=
HDRS    :=
CLEAN   :=

LIBC_SRCS  :=
LIBC_HDRS  :=
LIBC_CLEAN :=

$(foreach dir,$(SRCDIRS),$(eval $(eval CWD := $(dir)) $(eval include $(dir)/rules.mk)))

OBJS := $(patsubst %.c,%.o,$(SRCS))
OBJS := $(patsubst %.S,%.o,$(OBJS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

LIBC_OBJS := $(patsubst %.c,%.o,$(LIBC_SRCS))
LIBC_OBJS := $(patsubst %.S,%.o,$(LIBC_OBJS))
LIBC_DEPS := $(patsubst %.o,%.d,$(LIBC_OBJS))

# Include dependency files
-include $(DEPS)

#$(info DIRS=$(SRCDIRS))
#$(info SRCS=$(SRCS))
#$(info HDRS=$(HDRS))
#$(info OBJS=$(OBJS))
#$(info DEPS=$(DEPS))

$(OS_IMAGE): $(OBJS) $(KERNEL_LIBC)
	@$(Q1) [LD] $@
	$(Q2)$(CC) -T kernel.ld -static -Llibc -lk $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OS_IMAGE) $(OBJS) $(CLEAN)

depclean:
	rm -rf $(DEPS)

libc_clean:
	rm -rf $(KERNEL_LIBC) $(USER_LIBC) $(LIBC_OBJS) $(LIBC_CLEAN)

libc_depclean:
	rm -rf $(LIBC_DEPS)

superclean: depclean clean libc_depclean libc_clean

iso: $(OS_IMAGE)
	@tools/makeiso.sh $(OS_IMAGE) iso

## LIBC
$(KERNEL_LIBC): $(LIBC_OBJS)
#	@echo [AR RULE]
#	@echo ARFLAGS = $(ARFLAGS)
#	@echo $(@D)_ARFLAGS = $($(@D)_ARFLAGS)
#	@echo $@_ARFLAGS = $($@_ARFLAGS)
	@$(Q1) [AR]   $@
	$(Q2)$(AR) $(ARFLAGS) $($(@D)_ARFLAGS) $($@_ARFLAGS) $@ $^


####################
# EXPLICIT RULES
####################

# C explicit rule
%.o: %.c
#	@echo [C RULE]
#	@echo CFLAGS = $(CFLAGS)
#	@echo $(@D)_CFLAGS = $($(@D)_CFLAGS)
#	@echo $@_CFLAGS = $($@_CFLAGS)
	@$(Q1) [CC]   $@
	$(Q2)$(CC) $(CFLAGS) $($(@D)_CFLAGS) $($@_CFLAGS) -o $@ -c $<

# Assembler
%.o: %.S
#	@echo [ASM RULE]
#	@echo ASFLAGS = $(ASFLAGS)
#	@echo $(@D)_ASFLAGS = $($(@D)_ASFLAGS)
#	@echo $@_ASFLAGS = $($@_ASFLAGS)
	@$(Q1) [AS]   $@
	$(Q2)$(CC) $(ASFLAGS) $($(@D)_ASFLAGS) $($@_ASFLAGS) -o $@ -c $<

# Archive
%.a: %.o
#	@echo [AR RULE]
#	@echo ARFLAGS = $(ARFLAGS)
#	@echo $(@D)_ARFLAGS = $($(@D)_ARFLAGS)
#	@echo $@_ARFLAGS = $($@_ARFLAGS)
	@$(Q1) [AR]   $@
	$(Q2)$(AR) $(ARFLAGS) $($(@D)_ARFLAGS) $($@_ARFLAGS) -o $@ -c $<

####################
# Utility targets
####################
.PHONY: cscope
cscope:
	@echo -en Generating cscope files.
	@find . -name "*.c" >  cscope.files
	@echo -en .
	@find . -name "*.h" >> cscope.files
	@echo -en .
	
	@echo -en .
	@find . -name "*.mk" >> cscope.files
	@echo -en .
	@find . -name "Makefile" >> cscope.files
	@echo -en .
	@cscope -bqk
	@rm -f cscope.files
	@echo -e done
