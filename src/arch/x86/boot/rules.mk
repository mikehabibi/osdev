$(info CWD=$(CWD))
SRCS += $(CWD)/boot.S
HDRS += $(CWD)/multiboot.h

$(CWD)_ASFLAGS        := -I$(CWD)
$(CWD)_CFLAGS         := -I$(CWD)
