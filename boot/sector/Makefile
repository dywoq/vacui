# Tools
AS := as
LD := ld
OBJCOPY := objcopy

# Flags
ASFLAGS := --32
LDFLAGS  := -m elf_i386 -T linker.ld -nostdlib --gc-sections

# Target folders
BUILD := .build
TARGET := $(BUILD)/sector.bin

# Modules
MODULES := sector

# Sources
SRCS_AS := $(foreach m, $(MODULES), $(wildcard $(m)/*.S))
OBJS := $(patsubst %.S, $(BUILD)/%.o, $(SRCS_AS))

all: $(TARGET)

$(TARGET): $(OBJS)
	$(LD) $(LDFLAGS) $^ -o $@.elf
	$(OBJCOPY) -O binary -S $@.elf $@

$(BUILD)/%.o: %.S | dirs
	$(AS) $(ASFLAGS) -o $@ $<

dirs:
	@$(foreach m, $(MODULES), mkdir -p $(BUILD)/$(m);)

clean:
	rm -rf $(BUILD) 
