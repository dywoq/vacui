# ====================
# Default settings
# ====================
CC := gcc
LD := ld
OBJCOPY := objcopy
BUILD := build/

# ====================
# GNU EFI 
# ====================
GNUEFI ?= /usr/lib
CRT0 := $(GNUEFI)/crt0-efi-x86_64.o
LD_SCRIPT := $(GNUEFI)/elf_x86_64_efi.lds

# ====================
# Flags
# ====================
C_FLAGS := -fno-stack-protector -fpic -fshort-wchar -Wall -Wextra -c -Iinclude/ -I../shared/include/ --std=c23
LD_FLAGS := -nostdlib -znocombreloc --no-relax -T $(LD_SCRIPT) -shared -Bsymbolic $(CRT0) -L$(GNUEFI) -lgnuefi -lefi 
OBJCOPY_FLAGS := \
	-j .text \
	-j .sdata \
	-j .data \
	-j .rodata \
	-j .dynamic \
	-j .dynsym \
	-j .rel \
	-j .rela \
	-j .reloc \
	--target=efi-app-x86_64

TARGET := $(BUILD)/BOOTX64.efi

# ====================
# Sources, .o and .so
# files
# ====================
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c,$(BUILD)/%.o,$(SRCS))
SOS := $(patsubst $(BUILD)/%.o,$(BUILD)/%.so,$(OBJS))

# ====================
# Building
# ====================

all: $(TARGET)

$(TARGET): $(SOS) | $(BUILD)
	@$(OBJCOPY) $(OBJCOPY_FLAGS) $^ $@

$(BUILD)/%.so: $(BUILD)/%.o | $(BUILD)
	@$(LD) $(LD_FLAGS) $< -o $@

$(BUILD)/%.o: src/%.c | $(BUILD)
	@$(CC) $(C_FLAGS) $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

clean:
	@rm -fr $(BUILD) $(TARGET)
