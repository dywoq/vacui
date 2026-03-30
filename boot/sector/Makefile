# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero\

# Makefile configuration for building Zero boot sector

ASM := nasm
ASMFLAGS := -f bin

SECTOR := sector.S
BUILD := .build
TARGET := $(BUILD)/sector.bin

all: $(TARGET)

$(TARGET): $(SECTOR) $(BUILD)
	@echo " ASM $(SECTOR)"
	@$(ASM) $(ASMFLAGS) $(SECTOR) -o $(TARGET)
	@echo "Building is complete."
$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@echo " RM $(BUILD)"
	@rm $(BUILD) -fr

