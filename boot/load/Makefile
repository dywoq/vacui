# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

CC ?= gcc
CFLAGS  ?= -Wall \
	-Wextra \
	-Iinclude \
	-I../../include \
	--std=gnu23 \
	-Wstack-usage=16384 \
	-Wframe-larger-than=16384 \
	-m32 \
	-fno-pic \
	-fno-pie \
	-fno-stack-protector \
	-ffreestanding \
	-nostdlib
	
AS ?= as
ASFLAGS := --32

LD ?= ld
LDFLAGS := -T load.ld -nostdlib

BUILD = .build
TARGET  ?= $(BUILD)/load.bin
PYTHON := python3

MODULES := hub

SRCS_C := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRCS_C)) \
	$(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

all: config $(TARGET)

$(TARGET): $(OBJS)
	@echo " LD $@"
	@$(LD) $(LDFLAGS) $^ -o $@

$(BUILD)/%.o: %.c | dirs
	@echo " CC $<"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BUILD)/%.o: %.S | dirs
	@echo " AS $<"
	@$(AS) $(ASFLAGS) $< -o $@

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

config:
	@echo " PYTHON .scripts/kconfig/boot-load-gen.py"
	@$(PYTHON) ./scripts/kconfig/boot-load-gen.py

menuconfig:
	@kconfig-mconf Kconfig
	@echo " PYTHON ./scripts/kconfig/boot-load-gen.py"
	@$(PYTHON) ./scripts/kconfig/boot-load-gen.py

clean:
	@echo " RM $(BUILD)"
	@rm -rf $(BUILD) include/zero/boot/load/autoconf.h

