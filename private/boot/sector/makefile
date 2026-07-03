# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Description:
#
# 	Boot sector Makefile	

#
# Compilers
#
ASM := nasm
ASMFLAGS := -f bin

#
# Target, build directory and source file
#
BUILD_DIR := .build
SECTOR := sector.S
TARGET := $(BUILD_DIR)/sector.bin

#
# Building
#
all: $(BUILD_DIR) $(TARGET)

$(TARGET): $(SECTOR)
	$(ASM) $(ASMFLAGS) $(SECTOR) -o $(TARGET)
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -fr $(BUILD_DIR)

help:
	@echo "	all	Build boot sector"
	@echo "	clean	Clean build artifacts"

