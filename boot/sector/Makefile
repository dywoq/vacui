# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

ASM := uasm
ASMFLAGS := -bin

BUILD := .build
TARGET := $(BUILD)/sector.bin

SECTOR := sector.S

all: $(TARGET)

$(TARGET): $(BUILD)
	@echo " ASM   $(TARGET)"
	@$(ASM) $(ASMFLAGS) -Fo $(TARGET) $(SECTOR)

$(BUILD):
	@echo " MKDIR $(BUILD)"
	@mkdir $(BUILD) -p
clean:
	@rm $(BUILD) -fr
