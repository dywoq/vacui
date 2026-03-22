# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

NASM := nasm
NASM_FLAGS := -f bin

SECTOR := sector.S

BUILD := .build
TARGET := $(BUILD)/sector.bin

all: $(TARGET)

$(TARGET): $(BUILD) $(SECTOR)
	@echo " NASM $(SECTOR)"
	@$(NASM) $(NASM_FLAGS) $(SECTOR) -o $(TARGET)
$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@echo " RM $(BUILD)"
	@rm $(BUILD) -fr

