#
# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
# 
# Module Description
# 
#       VQBoot primary stage Makefile
#

FLAGS_C := -std=c23 \
	-I../../inc \
	-I../../hlb/inc

FLAGS_LINKER := -L../../lib \
	-lbase_hlbvid \
	-lbase_hlbdisk

LINKER_ENTRY_FUNCTION := PrimaryStartup
LINKER_ADDRESS := 0x8000
include ../../templates/x86_16-bare-metal-program.mk
