# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

CC ?= gcc
CFLAGS  ?= -Wall \
	-Wextra \
	-Iinclude \
	--std=gnu23 \
	-Wstack-usage=16384 \
	-Wframe-larger-than=16384 \
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
	
ASM ?= nasm
ASMFLAGS := -f elf32

LD ?= ld
LDFLAGS := -T kernel.ld -nostdlib --gc-sections -s --build-id=none

BUILD = .build
TARGET  ?= $(BUILD)/kernel.bin
PYTHON := python3

MODULES := hub

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
	@echo " PYTHON ./scripts/kconfig/kernel-gen.py"
	@$(PYTHON) ./scripts/kconfig/kernel-gen.py

menuconfig:
	@kconfig-mconf Kconfig
	@echo " PYTHON ./scripts/kconfig/kernel-gen.py"
	@$(PYTHON) ./scripts/kconfig/kernel-gen.py

clean:
	@echo " RM $(BUILD)"
	@rm -rf $(BUILD) include/zero/kernel/autoconf.h
