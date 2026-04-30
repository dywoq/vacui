ASM := nasm
ASM_FLAGS := -f bin

BUILD ?= .build
SECTOR := sector.S
TARGET := $(BUILD)/vqboot_sector.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(ASM) $(ASM_FLAGS) $(SECTOR) -o $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)
clean:
	rm -fr $(BUILD)
