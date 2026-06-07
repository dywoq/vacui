# Copyright 2026 dywoq - Apache License 2.0
# A part of https://github.com/dywoq/vacui

NASM := nasm
NASMFLAGS := -f bin

SECTOR := sector.S
BUILD := .build
TARGET := $(BUILD)/sector.bin

all: $(TARGET)

$(TARGET): $(BUILD)
	$(NASM) $(NASMFLAGS) $(SECTOR) -o $(TARGET)

$(BUILD):
	mkdir -p $(BUILD)
clean:
	rm -fr $(BUILD)
