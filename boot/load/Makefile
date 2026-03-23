# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/zero

NASM := nasm
NASM_FLAGS := -f bin

LOAD := load.S

BUILD := .build
TARGET := $(BUILD)/load.bin

all: $(TARGET)

$(TARGET): $(BUILD) $(LOAD)
	@echo " NASM $(LOAD)"
	@$(NASM) $(NASM_FLAGS) $(LOAD) -o $(TARGET)
$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@echo " RM $(BUILD)"
	@rm $(BUILD) -fr

