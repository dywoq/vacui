#
# Copyright 2026 dywoq - Apache License 2.0 
# https://github.com/dywoq/vacui
#
# Routine Description
#
# 	Makefile for building VQBoot sector stage 
#

#
# Tools
#

ASM 		:= nasm
ASMFLAGS 	:= -f bin

#
# Directories
#

BUILD_DIR 	:= .build

#
# Files
#

SECTOR 		:= sector.S
SECTOR_OUTPUT	:= $(BUILD_DIR)/vqsector.bin

#
# Buiilding rules
#

all: help

sector:
	@mkdir -p $(BUILD_DIR)
	@echo "	ASM	$(SECTOR) -> $(SECTOR_OUTPUT)"
	@$(ASM) $(ASMFLAGS) $(SECTOR) -o $(SECTOR_OUTPUT)
	@echo "Successfully compiled the sector stage: $(SECTOR_OUTPUT)"

clean:
	@rm -fr $(BUILD_DIR)

help:
	@echo "Available commands:"
	@echo "	* sector	Build the VQBoot sector stage binary"
	@echo "	* clean		Clean the build artifacts, such as $(BUILD_DIR) directory"
