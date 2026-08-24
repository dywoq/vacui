#
# Copyright 2026 dywoq - Apache License 2.0 
# https://github.com/dywoq/vacui
#
# Routine Description
#
# 	Makefile for building VQ Kernel
#

LINKER_ADDRESS := 0x8000
LINKER_ENTRY_FUNCTION := Startup
FLAGS_C += -I../inc -I../../inc -I../../hlb/inc -std=c23
FLAGS_LINKER += -L../../lib -lhlbvid

include ../../templates/x86_16-bare-metal-program.mk
