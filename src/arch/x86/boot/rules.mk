SRCS += $(CWD)/boot.S
SRCS += $(CWD)/bios.S
HDRS += $(CWD)/multiboot.h

$(CWD)_ASFLAGS        := -I$(CWD)
$(CWD)_CFLAGS         := -I$(CWD)
