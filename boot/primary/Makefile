# Tools
CC := gcc
AS := as
LD := ld
OBJCOPY := objcopy

# Flags
CFLAGS := -fno-pie -fno-pic -Iinclude/ -I../../include/ -nostdlib --std=c23 -m32
ASFLAGS := --32
LDFLAGS  := -m elf_i386 -T linker.ld -nostdlib --gc-sections

# Target folders
BUILD := .build
TARGET := $(BUILD)/primary.bin

# Modules
MODULES := hub bios

# Sources
SRCS_C := $(foreach m, $(MODULES), $(wildcard $(m)/*.c)) 
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.c, $(BUILD)/%.o, $(SRCS_C)) \
		$(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

all: $(TARGET)

$(TARGET): $(BUILD)/entry/_start.o $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@.elf
	$(OBJCOPY) -O binary -S $@.elf $@

$(BUILD)/%.o: %.c | dirs
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILD)/%.o: %.S | dirs
	$(AS) $(ASFLAGS) -o $@ $<

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

clean:
	rm -rf $(BUILD) 
