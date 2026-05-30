# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

# The i386 config

export CC=gcc
export LD=ld
export OBJCOPY=objcopy
export AS=nasm

I386_BUILD_DIR := .build/i386

bal: $(I386_BUILD_DIR)
	make -C bal/i386
	cp bal/i386/sector/.build/sector.bin .build/i386/sector.bin
	cp bal/i386/primary/.build/primary.bin .build/i386/primary.bin
	cp bal/i386/final/.build/final.bin .build/i386/final.bin
bal_clean:
	make clean -C bal/i386
	rm $(I386_BUILD_DIR) -fr
$(I386_BUILD_DIR):
	mkdir -p $(I386_BUILD_DIR)
