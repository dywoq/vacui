# -----------------------------
# Toolchain
# -----------------------------
CC := smlrcc
AS := nasm

# Build directory
BUILD := build

# Flags
CFLAGS := -flat16 -c -S -Iinclude
ASMFLAGS := -f bin

# Source files
C_SOURCES := $(wildcard src/*.c)
ASM_SOURCES := $(wildcard src/*.asm)

# Object / intermediate files
C_ASM := $(patsubst src/%.c,$(BUILD)/%.asm,$(C_SOURCES))
C_OBJS := $(patsubst src/%.c,$(BUILD)/%.bin,$(C_SOURCES))
ASM_OBJS := $(patsubst src/%.asm,$(BUILD)/%.bin,$(ASM_SOURCES))
OBJS := $(ASM_OBJS) $(C_OBJS)

# Output binary
OS_IMG := vacuios.img
KERNEL := $(BUILD)/$(OS_IMG)

# -----------------------------
# Default target
# -----------------------------
all: $(KERNEL)

# -----------------------------
# Compile C to NASM assembly
# -----------------------------
$(BUILD)/%.asm: src/%.c | $(BUILD)
	$(CC) $(CFLAGS) -o $@ $<

# -----------------------------
# Assemble C NASM assembly to flat binary
# -----------------------------
$(BUILD)/%.bin: $(BUILD)/%.asm | $(BUILD)
	$(AS) $(ASMFLAGS) $< -o $@

# -----------------------------
# Assemble ASM files
# -----------------------------
$(BUILD)/%.bin: src/%.asm | $(BUILD)
	$(AS) $(ASMFLAGS) $< -o $@

# -----------------------------
# Combine bootloader + kernel
# -----------------------------
$(KERNEL): $(OBJS)
	cat $(OBJS) > $(KERNEL)

# -----------------------------
# Build directory
# -----------------------------
$(BUILD):
	mkdir -p $(BUILD)

# -----------------------------
# Clean
# -----------------------------
clean:
	rm -rf $(BUILD)/*

# -----------------------------
# Run in QEMU
# -----------------------------
qemu: clean all
	qemu-system-i386 $(BUILD)/$(OS_IMG)
