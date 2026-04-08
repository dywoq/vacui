# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

CXX := riscv64-linux-gnu-g++
CXXFLAGS := -Wall \
    -Wextra \
    -Iinclude \
    -I../include \
    --std=gnu++2c \
    -march=rv64gc \
    -mabi=lp64d \
    -mcmodel=medany \
    -fno-pic \
    -fno-pie \
    -fno-stack-protector \
    -ffreestanding \
    -nostdlib \
    -fno-asynchronous-unwind-tables \
    -fno-unwind-tables \
    -fno-ident \
    -ffunction-sections \
    -fdata-sections \
    -fno-rtti \
    -fno-exceptions

ASM := riscv64-linux-gnu-as
ASMFLAGS := -march=rv64gc -mabi=lp64d

LD := riscv64-linux-gnu-ld
LDFLAGS  := -T kernel.ld -nostdlib --gc-sections

OBJCOPY ?= riscv64-linux-gnu-objcopy

BUILD = .build
TARGET  ?= $(BUILD)/kernel.bin

GEN_KCONFIG := scripts/gen-kconfig.py
PYTHON := python3

MODULES := hub utility base \
	   devices task

SRCS_CXX := $(foreach m, $(MODULES), $(wildcard $(m)/*.cxx))
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.cxx, $(BUILD)/%.o, $(SRCS_CXX)) \
	$(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

# ----------- Building --------------
all: config $(TARGET)

$(TARGET): $(OBJS)
	@echo " LD      $@.elf"
	@$(LD) $(LDFLAGS) $^ -o $@.elf
	@echo " OBJCOPY $@"
	@$(OBJCOPY) -O binary $@.elf $@

$(BUILD)/%.o: %.cxx | dirs
	@echo " CXX 	 $<"
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S | dirs
	@echo " ASM 	 $<"
	@$(ASM) $(ASMFLAGS) $< -o $@

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

# ----------- Configuration --------------
config:
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
menuconfig:
	@kconfig-mconf Kconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
nconfig:
	@kconfig-nconf Kconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
allnoconfig:
	@kconfig-conf Kconfig --allnoconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
allyesconfig:
	@kconfig-conf Kconfig --allyesconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
allmodconfig:
	@kconfig-conf Kconfig --allmodconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
alldefconfig:
	@kconfig-conf Kconfig --alldefconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)
randconfig:
	@kconfig-conf Kconfig --randconfig
	@echo " PYTHON $(GEN_KCONFIG)"
	@$(PYTHON) $(GEN_KCONFIG)

# ----------- Cleaning --------------
clean:
	@echo " RM $(BUILD)"
	@rm -rf $(BUILD) include/zero/boot/autoconf.h
