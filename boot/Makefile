# Copyright 2026 - Apache License 2.0
# A part of https://github.com/dywoq/zero

NASM := nasm
NASM_FLAGS := -f bin

SECTOR := sector.S

BUILD := .build
TARGET := $(BUILD)/sector.bin

all: $(TARGET)
	
$(TARGET): $(SECTOR) $(BUILD)
	@echo " NASM $(SECTOR)"
	@$(NASM) $(NASM_FLAGS) $(SECTOR) -o $(TARGET)

$(BUILD):
	@mkdir $(BUILD) -p
clean:
	@rm $(BUILD) -fr
