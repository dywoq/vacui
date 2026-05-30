# Copyright 2026 dywoq - Apache License 2.0
# https://github.com/dywoq/vacui

CFLAGS := -m32 -nostdlib -c -fno-pie -fno-pic -fno-stack-protector -std=c90 \
			-Iinc -I../../../inc -I../../inc -Os
LDFLAGS := --gc-sections -nostdlib -s -T final.ld -flto
ASFLAGS := -f elf32

BUILD = .build
TARGET  ?= $(BUILD)/final.bin
MODULES := hub

SRCS_C := $(foreach m, $(MODULES), $(wildcard $(m)/*.c))
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRCS_C)) \
	$(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo " LD $@.elf"
	@$(LD) $(LDFLAGS) $^ -o $@.elf
	@echo " OBJCOPY $@"
	@$(OBJCOPY) -O binary $@.elf $@
	@rm $@.elf

$(BUILD)/%.o: %.c | dirs
	@echo " CC $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S | dirs
	@echo " ASM $<"
	@$(AS) $(ASFLAGS) $< -o $@

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

$(BUILD):
	mkdir -p $(BUILD)

clean:
	rm $(BUILD) -fr