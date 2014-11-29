# NOTE: This is my attempt at a non-recursive Makefile. For more information,
# read "Recursive Make Considered Harmful".

# Architecture. Eventually this may be set by config options, but for now since
# we know this is a simple x86 OS, no need to do any of that now.
ARCH     := x86

# Final image name for OS
OS_IMAGE := osdev.bin

# Toolchain information
CROSS := i686-elf-
CC    := $(CROSS)gcc
LD    := $(CROSS)ld
AS    := $(CROSS)as
CPP   := $(CROSS)cpp

# Common compilation flags
CFLAGS   += -nostdlib -lgcc -std=gnu99 -MMD -ffreestanding -Wall -Werror
LDFLAGS  += -nostdlib -lgcc
ASFLAGS  += $(CFLAGS)

#######
# Rules
#######
SRCDIRS := arch/$(ARCH)

#SRCS := $(shell find $(SRCDIRS) -type f -name "*.c" -o -name "*.S")
#HDRS := $(shell find $(SRCDIRS) -type f -name "*.h")
SRCS    :=
HDRS    :=
CLEAN   :=

$(foreach dir,$(SRCDIRS),$(eval $(eval CWD := $(dir)) $(eval include $(dir)/rules.mk)))

OBJS := $(patsubst %.c,%.o,$(SRCS))
OBJS := $(patsubst %.S,%.o,$(OBJS))
DEPS := $(patsubst %.o,%.d,$(OBJS))

# Include dependency files
-include $(DEPS)

$(info DIRS=$(SRCDIRS))
$(info SRCS=$(SRCS))
$(info HDRS=$(HDRS))
$(info OBJS=$(OBJS))
$(info DEPS=$(DEPS))

.PHONY: all clean depclean superclean
all: $(OS_IMAGE)
	@echo "Successfully built kernel."

$(OS_IMAGE): $(OBJS)
	$(CC) -T kernel.ld $(CFLAGS) $^ -o $@

clean:
	rm -rf $(OBJS) $(CLEAN)

depclean:
	rm -rf $(DEPS)

superclean: depclean clean

####################
# EXPLICIT RULES
####################

# C explicit rule
%.o: %.c
#	@echo [C RULE]
#	@echo CFLAGS = $(CFLAGS)
#	@echo $(@D)_CFLAGS = $($(@D)_CFLAGS)
#	@echo $@_CFLAGS = $($@_CFLAGS)
	$(CC) $(CFLAGS) $($(@D)_CFLAGS) $($@_CFLAGS) -o $@ -c $<

# Assembler
%.o: %.S
#	@echo [ASM RULE]
#	@echo ASFLAGS = $(ASFLAGS)
#	@echo $(@D)_ASFLAGS = $($(@D)_ASFLAGS)
#	@echo $@_ASFLAGS = $($@_ASFLAGS)
	$(CC) $(ASFLAGS) $($(@D)_ASFLAGS) $($@_ASFLAGS) -o $@ $<

