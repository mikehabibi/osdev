# x86 arch Makefile
SRCS +=
HDRS +=

# Custom flags for this directory
$(CWD)_CFLAGS        :=

# Subdirs
MYCWD := $(CWD)

CWD   := $(MYCWD)/boot
include $(CWD)/rules.mk
