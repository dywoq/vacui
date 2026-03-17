# Copyright 2026 - Apache License 2.0
# A part of https://github.com/dywoq/zero

# Tools
CC := gcc
CFLAGS := -fno-stack-protector \
		  -fno-pic -fno-pie \
	      -m16 \
		  -I../include/ \
		  -c \
		  --std=c23 \
		  -ffunction-sections \
		  -fdata-sections

LD := i686-elf-ld
LDFLAGS := -T linker.ld --oformat binary -s -n

AS := i686-elf-as
ASFLAGS :=

# Target
BUILD := .build
TARGET := $(BUILD)/kernel.bin

# Modules
SRC =
OBJ =

include bios/Makefile
include hub/Makefile
include std/Makefile

# Build type
BUILD_TYPE ?= debug
ifeq ($(BUILD_TYPE), debug)
	CFLAGS += -DDEBUG=1  -DRELEASE=0
endif

ifeq ($(BUILD_TYPE), release)
	CFLAGS += -DDEBUG=0  -DRELEASE=1
endif

# Building
all: $(TARGET)
	@echo "Building for $(BUILD_TYPE) mode"
	
$(TARGET): $(BUILD) $(OBJ)
	@$(LD) $(LDFLAGS) $(OBJ) -o $(TARGET)
$(BUILD)/%.o: %.c
	@echo " CC $<"
	@@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $< -o $@
$(BUILD)/%.o: %.S
	@echo " AS $<"
	@mkdir -p $(dir $@)
	@$(AS) $(ASFLAGS) $< -o $@

$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@echo " RM $(BUILD)"
	@rm $(BUILD) -fr