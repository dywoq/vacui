#
# Copyright 2026 dywoq - Apache License 2.0 
# https://github.com/dywoq/vacui
#
# Routine Description
#
# 	Makefile for building VQ Kernel
#

#
# Tools
#
CC 	:= gcc
CFLAGS  := -std=c23 		\
	-m32 			\
	-ffreestanding 		\
	-fno-pic 

LD := ld
LDFLAGS := -T vqke.ld 	\
	-m elf_i386

ASM := nasm
ASMFLAGS := -f elf32

OBJCOPY := objcopy

#
# Target and directories
#
BUILD_DIR 	:= .build
OBJS_DIR 	:= .objs
TARGET		:= $(BUILD_DIR)/vqke.bin

#
# Modules
#
MODULES := ke
SOURCES := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
SOURCES_ASM := $(foreach m, $(MODULES), $(wildcard $(m)/*.S)) 
OBJECTS := $(foreach m, $(MODULES), $(SOURCES:$(m)/%.c=$(OBJS_DIR)/$(m)/%.o)) \
	$(foreach m, $(MODULES), $(SOURCES_ASM:$(m)/%.S=$(OBJS_DIR)/$(m)/%.o))

#
# Building rules
#

all: $(BUILD_DIR) $(OBJS_DIR) CreateModuleDirsInObjs $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "	LD	$(TARGET).elf"
	@$(LD) $(LDFLAGS) -o $(TARGET).elf $(OBJECTS)
	@echo "	OBJCOPY	$(TARGET).elf -> $(TARGET)"
	@$(OBJCOPY) -O binary $(TARGET).elf $(TARGET)
$(OBJS_DIR)/%.o: %.c
	@echo "	CC	$< -> $@"
	@$(CC) $(CFLAGS) -c -o $@ $<
$(OBJS_DIR)/%.o: %.S
	@echo "	ASM	$< -> $@"
	@$(ASM) $(ASMFLAGS) -o $@ $<

CreateModuleDirsInObjs:
	@$(foreach m, $(MODULES), mkdir -p $(OBJS_DIR)/$(m);)
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
clean:
	@rm -fr $(BUILD_DIR) $(OBJS_DIR)

