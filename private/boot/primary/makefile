# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui
#
# Description:
#
# 	Boot primary stage Makefile	

#
# Compilers
#
CC := smlrcc
CCFLAGS := -flat16
CCORIGIN := 0x8000

ASM := nasm
ASMFLAGS := -f elf 

#
# Directories
#
BUILD_DIR := .build
OBJECTS_DIR := .objs

#
# Collect C and Assembly source files,
# transforming them into object files.
#

STARTUP_FILE := startup.S
STARTUP_FILE_OBJ := $(OBJECTS_DIR)/startup.o

C_SOURCES := $(wildcard *.c)
C_OBJECTS := $(C_SOURCES:%.c=$(OBJECTS_DIR)/%.o)

# Remove the startup file from the sources,
# because we need to put the startup file's object file
# into the start of the list.
ASM_SOURCES := $(filter-out $(STARTUP_FILE), $(wildcard *.S))
ASM_OBJECTS := $(ASM_SOURCES:%.S=$(OBJECTS_DIR)/%.o)

#
# Target, build directory
#
PRIMARY := primary.S
TARGET := $(BUILD_DIR)/primary.bin

#
# Building
#
all: $(BUILD_DIR) $(OBJECTS_DIR) $(TARGET)

$(TARGET): $(STARTUP_FILE_OBJ) $(C_OBJECTS) $(ASM_OBJECTS)
	$(CC) -origin $(CCORIGIN) $(CCFLAGS) -o $(TARGET) $(STARTUP_FILE_OBJ) $(C_OBJECTS) $(ASM_OBJECTS) 

#
# Build asssembly, C source files and startup file
#
$(STARTUP_FILE_OBJ): $(STARTUP_FILE)
	$(ASM) $(ASMFLAGS) $(STARTUP_FILE) -o $(STARTUP_FILE_OBJ)
$(OBJECTS_DIR)/%.o: %.c
	$(CC) $(CCFLAGS) -c -o $@ $<
$(OBJECTS_DIR)/%.o: %.S
	$(ASM) $(ASMFLAGS) -o $@ $<

#
# Create directories
#
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
$(OBJECTS_DIR):
	mkdir -p $(OBJECTS_DIR)

clean:
	rm -fr $(OBJECTS_DIR)
	rm -fr $(BUILD_DIR)

help:
	@echo "	all	Build boot sector"
	@echo "	clean	Clean build artifacts"

