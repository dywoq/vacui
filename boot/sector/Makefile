# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

ASM := nasm
ASMFLAGS := -f bin

BUILD := .build
TARGET := $(BUILD)/sector.bin

SECTOR := sector.S

all: $(TARGET)

$(TARGET): $(BUILD)
	@echo " ASM   $(TARGET)"
	@$(ASM) $(ASMFLAGS) -o $(TARGET) $(SECTOR)

$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@rm $(BUILD) -fr
