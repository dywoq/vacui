# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

CC ?= gcc
CFLAGS  ?= -Wall \
	-Wextra \
	-Iinclude \
	-I../../shared/include \
	--std=gnu23 \
	-m32 \
	-fno-pic \
	-fno-pie \
	-fno-stack-protector \
	-ffreestanding \
	-nostdlib \
	-fno-asynchronous-unwind-tables \
	-fno-unwind-tables \
    	-fno-ident \
    	-ffunction-sections \
    	-fdata-sections
	
ASM ?= as
ASMFLAGS := --32

LD ?= ld
LDFLAGS := -T load.ld -nostdlib --gc-sections -s --build-id=none -m elf_i386

BUILD = .build
TARGET  ?= $(BUILD)/load.bin

GEN_KCONFIG := scripts/gen-kconfig.py
PYTHON := python3

MODULES := entry

SRCS_C := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRCS_C)) \
	$(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

all: config $(TARGET)

$(TARGET): $(OBJS)
	@echo " LD $@.elf"
	@$(LD) $(LDFLAGS) $^ -o $@.elf
	@echo " OBJCOPY $@"
	@objcopy -O binary $@.elf $@
	@rm $@.elf

$(BUILD)/%.o: %.c | dirs
	@echo " CC $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD)/%.o: %.S | dirs
	@echo " ASM $<"
	@$(ASM) $(ASMFLAGS) $< -o $@

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

config:
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)

menuconfig:
	@kconfig-mconf Kconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)

clean:
	@echo " RM $(BUILD)"
	@rm -rf $(BUILD) include/zero/boot/autoconf.h
